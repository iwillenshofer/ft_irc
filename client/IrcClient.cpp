/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:55:35 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/17 22:16:02 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcClient.hpp"


/*
** IrcClient
*/

std::vector<IrcClient *> IrcClient::_instances;
bool IrcClient::_stop_clients = false;

IrcClient::IrcClient(void): _fd(0), _registered(false), _register_sent(false), _joined(false)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
	signal(SIGINT, _signalHandler);
	signal(SIGQUIT, _signalHandler); 
}

IrcClient::IrcClient(IrcClient const &cp) { *this = cp; }
IrcClient &IrcClient::operator=(IrcClient const &cp)
{
	_fd = cp._fd;
	_receive_buffer = cp._receive_buffer;
	_send_buffer = cp._send_buffer;
	_receive_queue = cp._receive_queue;
	_send_queue = cp._send_queue;
	_port = cp._port;
	_nickname = cp._nickname;
	_username = cp._username;
	_hostname = cp._hostname;
	_realname = cp._realname;
	_password = cp._password;
	_joined = cp._joined;
	_register_sent = cp._register_sent;
	_registered = cp._registered;

	return (*this);
}
IrcClient::~IrcClient() { }

/*
** Socket connection
*/

std::string IrcClient::get_random(std::vector<std::string>&v)
{
	int idx = rand() % v.size();
	return (v[idx]);
}

void	IrcClient::create_socket( void )
{
	_fd = socket(PF_INET, SOCK_STREAM, 0);
	int enable = 1;
	setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	if (_fd == -1)
		throw std::runtime_error("Unable to create socket.");
	return ;
}

void	IrcClient::connect_socket( std::string address, int port, std::string password )
{
	int ret;
	_server = address;
	_port = port;
	_password = password;

	std::memset(&_server_address, 0, sizeof(_server_address));
	_server_address.sin_family = AF_INET;
	server = gethostbyname(_server.c_str());
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

void IrcClient::registerClient (void)
{
	if (_register_sent)
		return ;
	Debug("PID: " + ft::to_string(getpid()) + " Register Client: " + _nickname);
	_send_queue.push_back("PASS " + _password + std::string(MSG_ENDLINE));
	_send_queue.push_back("NICK " + _nickname + std::string(MSG_ENDLINE));
	_send_queue.push_back("USER " + _username + " 0 * :" + _realname + std::string(MSG_ENDLINE));
	_register_sent = true;
}

void IrcClient::joinChannel (void)
{
	_send_queue.push_back("JOIN #brasil" + std::string(MSG_ENDLINE));
	sleep(3);
}

void IrcClient::sendMessage(void)
{
	if (static_cast<int>(rand() % (INT_MAX / 100)) == 1)
	{
		std::string message = get_random(_chats);
		_send_queue.push_back("PRIVMSG #brasil :" + message + std::string(MSG_ENDLINE));
		sleep(static_cast<int>(rand() % 5));
	}
}

void IrcClient::processCommands (void)
{
	for (std::vector<std::string>::iterator msg_it = _receive_queue.begin(); msg_it != _receive_queue.end();)
	{
		Message msg;
		Mask::Maskparts mask;
		try
		{
			msg = Message(*msg_it);
			mask = Mask::Maskparts(msg.prefix());
		}
		catch (const Message::EmptyMessage &e)
		{
			msg_it = _receive_queue.erase(msg_it);
			return;
		}
		catch (const Message::InputLineTooLong &e)
		{
			msg_it = _receive_queue.erase(msg_it);
			return ;
		}
		if (msg.command() == "001")
			_registered = true;
		else if (msg.command() == "PING")
			_send_queue.push_back(std::string("PONG") + MSG_ENDLINE);
		else if (msg.command() == "JOIN" &&  mask.nickname == _nickname)
			_joined = true;
		else if (msg.command() == "KICK" && msg.arguments().size() >= 2 && msg.arguments(1) == _nickname)
			_joined = false;
		else if (msg.command() == "433")
		{
			_register_sent = false;
			_nickname = "Guest" + ft::to_string(static_cast<int>(rand() % 9999));
		}

		msg_it = _receive_queue.erase(msg_it);
	}
}

void IrcClient::runClient(void)
{
	std::string lastname = get_random(_nicknames);
	lastname[0] = std::toupper(lastname[0]);
	_nickname = get_random(_nicknames).substr(0, SRV_MAXNICKLEN);
	_username = _nickname;
	_realname = _nickname + " " + lastname;	
	_realname[0] = std::toupper(lastname[0]);

	while (!(_stop_clients))
	{
		if (!(_registered))
			registerClient();
		else if (!(_joined))
			joinChannel();
		while (_send_queue.size())
			write();
		read();
		if (_receive_queue.size())
			processCommands();
		if (_registered && _joined)
			sendMessage();
	}
}


void IrcClient::read(void)
{
	std::vector<std::string> tmp;
	bzero(_buffer, BUFFERSIZE + 1);
	ssize_t rc = recv( _fd, _buffer, BUFFERSIZE, 0);
	if (rc > 0)
	{
		_receive_buffer += _buffer;
		tmp = ft::split(_receive_buffer, MSG_ENDLINE);
		_receive_queue.insert(_receive_queue.end(), tmp.begin(), tmp.end());
	}
	for (std::vector<std::string>::iterator it = _receive_queue.begin(); it != _receive_queue.end(); it++)
		Debug(_nickname + " <- " + *it, DBG_WARNING);
}

/*
** writes any queued message to client.
** if message if not fully sent, its remaining is kept on queue to be sent on
** the next loop.
*/

void IrcClient::write(void)
{
	int rc;

	if (!(_send_queue.size()))
		return;
	Debug(_nickname + " -> " + _send_queue.at(0));
	rc = send(_fd, _send_queue.at(0).c_str(), _send_queue.at(0).size(), MSG_NOSIGNAL);
	if (rc > 0)
		_send_queue.at(0).erase(0, rc);
	if (_send_queue.size() && !(_send_queue.at(0).size()))
		_send_queue.erase(_send_queue.begin());
}


/*
** _signalHandler and _close_all_connections are called upon CTRL+C, CTRL+\, CTRL+Z
*/

void IrcClient::_signalHandler( int signal )
{
	Debug("Interrupt Signal Received: " + ft::to_string(signal) + "... Closing Client.", DBG_WARNING);
	for (std::vector<IrcClient *>::iterator it = IrcClient::_instances.begin(); it !=  IrcClient::_instances.end(); it++)
		close((*it)->_fd);
	_stop_clients = true;
}
