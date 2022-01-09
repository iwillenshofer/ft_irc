/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:37:36 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/09 17:19:42 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"
#include <cerrno>

std::vector<WebServer *> WebServer::_instances; //static members must be defined
bool WebServer::_stop_server = false;

WebServer::WebServer(int port)
{
	signal(SIGINT, _signalHandler);
	signal(SIGQUIT, _signalHandler); 
	signal(SIGTSTP, _signalHandler);
	_instances.push_back(this);
	_init(port);
}

WebServer::WebServer(WebServer const &cp)
{
	_instances.push_back(this);
	*this = cp;
}

WebServer &WebServer::operator=(WebServer const &cp)
{
	this->_socket = cp._socket;
	this->_clients = cp._clients;
	return (*this);
}

WebServer::~WebServer(void)
{
	WebServer::_instances.erase(std::remove(WebServer::_instances.begin(), WebServer::_instances.end(), this), WebServer::_instances.end());
}

void WebServer::_init(int port)
{
	_socket = Socket(port);
	_clients.add(_socket.get_server_socket());
	Debug("Listening [" + ft::to_string(_socket.get_server_socket()) + "] on " + ft::to_string(port) + ".", DBG_INFO);
	RunServer();
}

void WebServer::_accept_clients(int fd)
{
	Debug("Accept FD?", DBG_DEV);
	int acc_fd;
	while ((acc_fd = accept(fd, NULL, NULL)) > 0 )
	{
		Debug("Accepting connection [" + ft::to_string(acc_fd) + "] on [" + ft::to_string(fd) + "]", DBG_INFO);
		_clients.add(acc_fd);
	}
}

void WebServer::RunServer(void)
{
	Debug("Running Server...", DBG_INFO);
	while (!(_stop_server))
	{
		int rc = 0;
		int fd = 0;
    	rc = poll(_clients.list(), _clients.size(), 1000);
		if (rc)
		{
			for (size_t idx = 0; idx < _clients.size(); idx++)
			{
				fd = _clients.get_fd(idx);
				if (_clients.get_revents(idx) & POLLHUP)
					_clients.clients[fd].set_hangup(true);
				else if (_clients.get_revents(idx) & POLLIN)
				{
					if (idx == 0)
						_accept_clients(fd);
					else
						_clients.clients[fd].read();
				}
				else if (_clients.get_revents(idx) & POLLOUT)
					_clients.clients[fd].write();
			}
		}
		else
		{
			Debug("Poll timed out", DBG_DEV);
		}
		_clients.remove_queued();
	}
}

void WebServer::_signalHandler( int signal )
{
	Debug("Interrupt Signal Received: " + ft::to_string(signal) + "... Closing Server.", DBG_WARNING);
	for (std::vector<WebServer *>::iterator it = WebServer::_instances.begin(); it !=  WebServer::_instances.end(); it++)
		(*it)->_close_all_connections();
	_stop_server = true;
}

void WebServer::_close_all_connections(void)
{
	pollfd *lst = _clients.list();
	for (size_t idx = 0; idx < _clients.size(); idx++)
		close(lst[idx].fd);
}
