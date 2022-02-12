/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:55:35 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/12 00:50:18 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcClient.hpp"

/*
** IrcClient
*/

int IrcClient::_instances_count = 0;

IrcClient::IrcClient(std::string address, int port): _fd(0), _connected(true)
{
	_instance = _instances_count;
	_instances_count++;
	_create_socket();
	_start(address, port);
}

IrcClient::IrcClient(IrcClient const &cp)
{
	_instance = _instances_count;
	_instances_count++;
	*this = cp;
}

IrcClient &IrcClient::operator=(IrcClient const &cp)
{
	_fd = cp._fd;
	return (*this);
}

IrcClient::~IrcClient()
{
	_instances_count--;
	end();
}

std::string IrcClient::_log_color()
{
	std::string str("\033[");
	str += ft::to_string(CLR_BOLD) +  ";";
	str += ft::to_string((_instance % CLR_RED) + CLR_RED) + "m";
	str += "(" + ft::to_string(_instance + 1) + ")";
	str += std::string("\033[0m");
	return (str);
}

void	IrcClient::_log(std::string s, bool kind, bool output)
{

	std::string str;
	std::string direction;
	int color;
	size_t pos;

	if (!(output))
		return;
	while((pos = s.find("\r\n")) != std::string::npos)
		s.erase(pos, 2);
	if (kind == LOG_SEND)
	{
		color = CLR_YELLOW;
		direction = "--> ";
	}
	else
	{
		color = CLR_CYAN;
		direction = "<-- ";
	}
	str = _log_color();
	str += " \033[";
	str += ft::to_string(CLR_BOLD) +  ";";
	str += ft::to_string(color) + "m";
	str += direction;
	str += std::string("\033[");
	str += ft::to_string(CLR_UNDERLINED) +  ";";
	str += ft::to_string(CLR_WHITE) + "m";
	str += s;
	str += std::string("\033[0m");
	std::cout << str << std::endl;
}

void	IrcClient::_create_socket( void )
{
	_fd = socket(PF_INET, SOCK_STREAM, 0);
	int enable = 1;
	setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	if (_fd == -1)
		throw std::runtime_error("Unable to create socket.");
	return ;
}

void	IrcClient::_start( std::string _address, int _port)
{
	struct hostent			*server;
	struct sockaddr_in		_server_address;
	int						ret;

	std::memset(&_server_address, 0, sizeof(_server_address));
	_server_address.sin_family = AF_INET;
	server = gethostbyname(_address.c_str());
	if (server == NULL)
		throw std::runtime_error("No Such Host.");
	bcopy((char *)server->h_addr, 
         (char *)&_server_address.sin_addr.s_addr,
         server->h_length);
	_server_address.sin_port = htons(_port);
	ret = connect(_fd, (struct sockaddr *) &_server_address, sizeof(_server_address));	
	if (ret == -1)
	{
		throw std::runtime_error("Error Connecting.");
		return ;
	}
	fcntl(_fd, F_SETFL, O_NONBLOCK);
}

void IrcClient::_read(bool verbose)
{
	std::vector<std::string> tmp;
	bzero(_buffer, BUFFERSIZE + 1);
	int rc;

	while (1)
	{
		rc = recv( _fd, _buffer, BUFFERSIZE, 0);
		_receive_buffer += _buffer;
		bzero(_buffer, BUFFERSIZE + 1);
		tmp = ft::split(_receive_buffer, MSG_ENDLINE);
		_receive_queue.insert(_receive_queue.end(), tmp.begin(), tmp.end());
		if (rc == 0)
			_connected = false;
		if (rc <= 0)
			break ;
	}
	for (std::vector<std::string>::iterator it = _receive_queue.begin(); it != _receive_queue.end(); it++)
		_log(*it, LOG_RECV, verbose);
	_receive_queue.clear();
}

/*
** writes any queued message to client.
** if message if not fully sent, its remaining is kept on queue to be sent on
** the next loop.
*/

void IrcClient::_write(void)
{
	int rc;

	while (_send_queue.size())
	{
		rc = send(_fd, _send_queue.at(0).c_str(), _send_queue.at(0).size(), MSG_NOSIGNAL);
		if (rc > 0)
		{
			_log(_send_queue.at(0), LOG_SEND);
			_send_queue.at(0).erase(0, rc);
		}
		if (_send_queue.size() && !(_send_queue.at(0).size()))
			_send_queue.erase(_send_queue.begin());
	}
}

void IrcClient::command(std::string command)
{
	_send_queue.push_back(command);
	_write();
}

void IrcClient::listen(bool verbose, int rate)
{
	for (int i = 0; i < 4; i++)
	{
		_read(verbose);
		usleep(rate);
	}
}

void IrcClient::end(void)
{
	close(_fd);
}

bool IrcClient::is_connected(void) { return (_connected); }
