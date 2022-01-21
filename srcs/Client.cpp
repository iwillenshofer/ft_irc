/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:55:35 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/20 22:43:06 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd): _fd(fd), _hangup(false), registered(false), is_ping(false)
{
	bzero(&mode, sizeof(mode));
	last_ping = time(NULL);
	hostname = _get_address();
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
	nickname = cp.nickname;
	realname = cp.realname;
	registered = cp.registered;
	mode = cp.mode;
	last_ping = cp.last_ping;
	is_ping = cp.is_ping;
	return (*this);
}
Client::~Client() { }

/*
** setters and getters.
*/
std::string Client::get_prefix(void) { return (std::string(":") + nickname + "!~" + username + "@" + hostname); }
size_t Client::get_send_queue_size(void) { return (_send_queue.size()); }
std::vector<std::string> &Client::get_send_queue(void) { return (_send_queue); }
std::vector<std::string> &Client::get_receive_queue(void) { return (_receive_queue); }
bool Client::get_hangup(void) { return (_hangup); }
void Client::set_hangup(bool v) { _hangup = v; }
int Client::get_fd(void) { return (_fd); }
void Client::set_fd(int fd) { _fd = fd; }

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
		tmp = ft::split(_receive_buffer, "\r\n");
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
			set_hangup(true);
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
	struct sockaddr_in sockinfo;
	socklen_t sockinfo_len = sizeof(sockinfo);

	getsockname(_fd, (struct sockaddr*)&sockinfo, &sockinfo_len);
	return (ft::to_string(inet_ntoa(sockinfo.sin_addr)));
}

