/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:55:35 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/23 10:21:29 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd): _fd(fd), _hangup(false), registered(false), is_ping(false)
{
	bzero(&mode, sizeof(mode));
	last_ping = time(NULL);
	joined_time = time(NULL);
}

Client::Client(Client const &cp) { *this = cp; }
Client &Client::operator=(Client const &cp)
{
	_fd = cp._fd;
	_receive_buffer = cp._receive_buffer;
	_send_buffer = cp._send_buffer;
	_receive_queue = cp._receive_queue;
	_send_queue = cp._send_queue;
	_hangup = cp._hangup;
	_hangup_message = cp._hangup_message;
	nickname = cp.nickname;
	realname = cp.realname;
	registered = cp.registered;
	mode = cp.mode;
	last_ping = cp.last_ping;
	joined_time = cp.joined_time;
	is_ping = cp.is_ping;
	return (*this);
}
Client::~Client() { }

/*
** setters and getters.
*/
std::string Client::get_prefix(void) { return (std::string(":") + nickname + "!" + username + "@" + hostname); }
size_t Client::get_send_queue_size(void) { return (_send_queue.size()); }
std::vector<std::string> &Client::get_send_queue(void) { return (_send_queue); }
std::vector<std::string> &Client::get_receive_queue(void) { return (_receive_queue); }
std::string &Client::get_hangup_message(void) { return (_hangup_message); }
bool Client::get_hangup(void) { return (_hangup); }

void Client::set_hangup(bool v, std::string msg)
{
	_hangup = v;
	_hangup_message = msg;
	if (v)
	{
		_send_queue.clear();
		_send_queue.push_back("ERROR :" + msg);
	}
}

int Client::get_fd(void) { return (_fd); }
void Client::set_fd(int fd)
{ 
	_fd = fd; 
	hostname = _get_address();
}

/*
** reads messages from the client. If message is incomplete,
** it is kept on buffer to be read on the next poll loop.
*/

void Client::read(void)
{
	std::vector<std::string> tmp;
	Debug("Read", DBG_DEV);
	bzero(_buffer, BUFFERSIZE + 1);
	ssize_t rc = recv( _fd, _buffer, BUFFERSIZE, 0);
	if (rc > 0)
	{
		is_ping = false;
		last_ping = time(NULL);
		_receive_buffer += _buffer;
		tmp = ft::split(_receive_buffer, MSG_ENDLINE);
		if (_receive_buffer.size() > MSG_MAXMSGSIZE * 2)
		{
			Commands commands(ERR_INPUTTOOLONG, this);
			_receive_buffer.erase(_receive_buffer.begin(), _receive_buffer.begin() + MSG_MAXMSGSIZE);
		}
		_receive_queue.insert(_receive_queue.end(), tmp.begin(), tmp.end());
	}
	else if (rc <= 0)
	{
		Debug("Read Error", (rc == 0 ? DBG_WARNING: DBG_ERROR));
		if (rc == 0)
		{
			Debug("HANGUP", DBG_WARNING);
			set_hangup(true, Commands::generate_errormsg(ERR_EOFFROMCLIENT));
		}
		// rc == 0 other side closed socket 
		// rc == -1 error;
		/*
		** kept for comments only, we will remove this.
		** We don't care for sending errors or client hangup:
		** if there's an error, the message is still there to be sent.
		** if the client hungup, it will be catched by the ping pong loop.
		*/
	}
}

/*
** writes any queued message to client.
** if message if not fully sent, its remaining is kept on queue to be sent on
** the next loop.
*/

void Client::write(void)
{
	int rc;
	Debug("Write", DBG_ERROR);
	if (!(_send_queue.size()))
		return;
	rc = send(_fd, _send_queue.at(0).c_str(), _send_queue.at(0).size(), 0);
	if (rc > 0)
		_send_queue.at(0).erase(0, rc);
	if (_send_queue.size() && !(_send_queue.at(0).size()))
		_send_queue.erase(_send_queue.begin());
}

std::string Client::_get_address(void)
{
	struct sockaddr_storage addr;
	struct sockaddr_in addr4;
	socklen_t addr_len = sizeof(addr);
	char buffer[INET6_ADDRSTRLEN];

	std::memset(&addr, 0, sizeof(addr));
	std::memset(&addr4, 0, sizeof(addr4));
	std::memset(&buffer, 0, sizeof(buffer));
	if ((getpeername(_fd,(struct sockaddr*)&addr,&addr_len)))
		return (SRV_UNKNOWNHOST);
	if (addr.ss_family == AF_INET6 && IN6_IS_ADDR_V4MAPPED(&((struct sockaddr_in6 *)&addr)->sin6_addr))
	{
		addr_len = sizeof(addr4);
		addr4.sin_family = AF_INET;
		addr4.sin_port = ((struct sockaddr_in6 *)&addr)->sin6_port;
		memcpy(&addr4.sin_addr.s_addr, ((struct sockaddr_in6 *)&addr)->sin6_addr.s6_addr + 12, sizeof(addr4.sin_addr.s_addr));
		memcpy(&addr, &addr4, sizeof(addr4));
	}
	if ((getnameinfo((struct sockaddr*)&addr, addr_len, buffer, sizeof(buffer), 0, 0, 0)))
		return (SRV_UNKNOWNHOST);
	return (std::string(buffer));
}

bool	Client::is_invisible(void) const
{
	return mode.i;
}

void	Client::set_invisible(void)
{
	mode.i = true;
}

void	Client::unset_invisible(void)
{
	mode.i = false;
}

bool	Client::is_receive_notices(void) const
{
	return mode.s;
}

void	Client::set_receive_notices(void)
{
	mode.s = true;
}

void	Client::unset_receive_notices(void)
{
	mode.s = false;
}

bool	Client::is_receive_wallops(void) const
{
	return mode.s;
}

void	Client::set_receive_wallops(void)
{
	mode.w = true;
}

void	Client::unset_receive_wallops(void)
{
	mode.w = false;
}

bool	Client::is_operator(void) const
{
	return mode.o;
}

void	Client::set_operator(void)
{
	mode.o = true;
}

void	Client::unset_operator(void)
{
	mode.o = false;
}
