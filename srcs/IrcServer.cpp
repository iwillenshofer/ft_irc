/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:37:36 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/17 22:27:56 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

std::vector<IrcServer *> IrcServer::_instances;
bool IrcServer::_stop_server = false;

IrcServer::IrcServer(void) { };

IrcServer::IrcServer(std::string host, int port, unsigned long password)
{
	signal(SIGINT, _signalHandler);
	signal(SIGQUIT, _signalHandler); 
	_instances.push_back(this);
	_server = Server(host, password);
	_connections = Connections(&_server);
	_init(port);
}

IrcServer::IrcServer(IrcServer const &cp)
{
	_instances.push_back(this);
	*this = cp;
}

IrcServer &IrcServer::operator=(IrcServer const &cp)
{
	this->_socket = cp._socket;
	this->_server = cp._server;
	this->_connections = cp._connections;
	return (*this);
}

IrcServer::~IrcServer(void)
{
	IrcServer::_instances.erase(std::remove(IrcServer::_instances.begin(), IrcServer::_instances.end(), this), IrcServer::_instances.end());
}

/*
** initializes Socket and adds it as the first elements on _connections list.
*/

void IrcServer::_init(int port)
{
	_socket = Socket(port);
	_connections.add(_socket.get_server_socket());
	Debug("Listening [" + ft::to_string(_socket.get_server_socket()) + "] on " + ft::to_string(port) + ".", DBG_INFO);
	RunServer();
}

/*
** Accepts a new connections if POLLIN triggered on Socket 
*/

void IrcServer::_accept_connections(int fd)
{
	int acc_fd;
	while ((acc_fd = accept(fd, NULL, NULL)) > 0 )
	{
		Debug("Accepting connection [" + ft::to_string(acc_fd) + "] on [" + ft::to_string(fd) + "]", DBG_INFO);
		_connections.add(acc_fd);
	}
}

/*
** main server loop.
** read, writes from/to client or accepts new connection.
** then, checks if connection is alive, removes any queued clients
** and process queued messages.
*/

void IrcServer::RunServer(void)
{
	Debug("Running Server...", DBG_INFO);
	while (!(_stop_server))
	{
		int rc = 0;
		int fd = 0;
    	rc = poll(_connections.list(), _connections.size(), 1000);
		if (rc)
		{
			for (size_t idx = 0; idx < _connections.size(); idx++)
			{
				fd = _connections.get_fd(idx);
				if (_connections.get_revents(idx) & POLLHUP)
					_connections.clients[fd].set_hangup(true, Commands::generate_errormsg(ERR_EOFFROMCLIENT));
				else if (_connections.get_revents(idx) & POLLIN)
				{
					if (idx == 0)
						_accept_connections(fd);
					else
						_connections.clients[fd].read();
				}
				else if (_connections.get_revents(idx) & POLLOUT)
					_connections.clients[fd].write();
				if (_connections.get_revents(idx) & (POLLIN | POLLOUT))
					break; /* so we dont read/write multiple times on the same poll loop */
			}
		}
		_connections.remove_queued();
		_connections.process_commands();
		_connections.pingpong();
	}
}

/*
** _signalHandler and _close_all_connections are called upon CTRL+C, CTRL+\, CTRL+Z
*/

void IrcServer::_signalHandler( int signal )
{
	Debug("Interrupt Signal Received: " + ft::to_string(signal) + "... Closing Server.", DBG_WARNING);
	for (std::vector<IrcServer *>::iterator it = IrcServer::_instances.begin(); it !=  IrcServer::_instances.end(); it++)
		(*it)->_close_all_connections();
	_stop_server = true;
}

void IrcServer::_close_all_connections(void)
{
	pollfd *lst = _connections.list();
	for (size_t idx = 1; idx < _connections.size(); idx++)
		close(lst[idx].fd);
	close(lst[0].fd);
}
