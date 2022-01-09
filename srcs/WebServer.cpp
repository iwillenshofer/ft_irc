/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:37:36 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/09 09:57:49 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"

std::vector<WebServer *> WebServer::_instances; //static members must be defined
bool WebServer::_stop_server = false;

WebServer::WebServer(std::string filename)
{
	signal(SIGINT, _signalHandler);
	signal(SIGQUIT, _signalHandler); 
	signal(SIGTSTP, _signalHandler);
	_instances.push_back(this);
	_init(filename);
}

WebServer::WebServer(WebServer const &cp)
{
	_instances.push_back(this);
	*this = cp;
}

WebServer &WebServer::operator=(WebServer const &cp)
{
	this->_binds = cp._binds;
	return (*this);
}

WebServer::~WebServer(void)
{
	WebServer::_instances.erase(std::remove(WebServer::_instances.begin(), WebServer::_instances.end(), this), WebServer::_instances.end());
}

void WebServer::_init(int port)
{
	_socket = Socket(port);
	Debug("Listening [" + ft::to_string(_server_socket) + "] on:" + ft::to_string(port) + ".", DBG_INFO);
	RunServer();
}

void WebServer::_initializeFDs(void)
{
	for (bind_type::iterator it = _binds.begin(); it !=  _binds.end(); it++)
		_fds.push_back(it->getSockedFD());
}

void WebServer::_checkFdError(int fd_idx)
{
	if(_fds[fd_idx].revents & (POLLNVAL|POLLERR|POLLHUP))
	{
		Debug("Connection Error.", DBG_ERROR);
		_fds.getAttr(fd_idx).socketError(true);
		_fds.getAttr(fd_idx).shouldClose(true);
	} 
}

void WebServer::_acceptFDs(int fd_idx)
{
	int acc_fd;
	while ((acc_fd = accept(_fds[fd_idx].fd, NULL, NULL)) > 0 )
	{
		Debug("Accepting connection [" + ft::to_string(acc_fd) + "] on " + getBind(_fds[fd_idx].fd)->getListenIP() + ":" + ft::to_string(getBind(_fds[fd_idx].fd)->getListenPort()) + ".", DBG_INFO);
		_fds.push_back(acc_fd, getBind(_fds[fd_idx].fd), FDKIND_ACCEPT);
	}
}

void WebServer::__setHeader(int fd_idx)
{
	size_t found_end;
	FileDescriptorAttributes *fda = &(_fds.getAttr(fd_idx));

	if (!(fda->getHeader().isSet()))
	{
		while ((found_end = fda->getContent().find("\r\n")) == 0)
			fda->setContent(_fds.getAttr(fd_idx).getContent().substr(2));
		found_end = fda->getContent().find("\r\n\r\n");
		if (found_end != std::string::npos)
		{
			Debug("Setting Header", DBG_DEV);
			fda->setHeader(fda->getContent());
			fda->headerError(fda->getHeader().Value().check_error());
		}
	}
}

void WebServer::__checkCompleteContent(int fd_idx)
{
	std::string s;
	size_t		content_length = 0;
	size_t		max_body_size = 0;
	size_t		current_recv_body = 0;
	FileDescriptorAttributes *fda = &(_fds.getAttr(fd_idx));

	Debug("Checking Completed for " + ft::to_string(_fds[fd_idx].fd) + "Addr: " + ft::to_string(fda), DBG_DEV);
	if (!(fda->getHeader().isSet()))
		return ;
	else
	{
		current_recv_body = fda->getContent().size() - fda->getHeader().Value().get_header_content().size();
		s = fda->getHeader().Value().get_field("Content-Length");
		if (s.size())
			content_length = std::atol(s.c_str());
		else
			content_length = 0;
		max_body_size = fda->getHeader().Value().getLocation().getClientMaxBodySize().Value();
		if (max_body_size && max_body_size < current_recv_body )
			fda->headerError(413);
		else if (content_length <= ( current_recv_body ))
			fda->completedContent(true);
	}
}

void WebServer::__checkKernelAvailable(int fd_idx)
{
	FileDescriptorAttributes *fda = &(_fds.getAttr(fd_idx));

	int i = _fds.getAvailable(_fds[fd_idx].fd); //gets the available data in kernel
	if (i == -1)
		fda->socketError(true);
	fda->kernelAvailable(i);
}


void WebServer::RunServer(void)
{
	FileDescriptorAttributes *fda; 

	_initializeFDs();
	Debug("Running Server...", DBG_INFO);
	while (!(_stop_server))
	{
		int rc = 0;
    	rc = poll(_fds.getFds(), _fds.size(), 500);
		if (rc)
		{
			for (size_t i = 0; i < _fds.size(); i++)
			{ 
				fda = &(_fds.getAttr(i));
				_checkFdError(i);
				if (fda->getKind() == FDKIND_SOCKET && _fds[i].revents == POLLIN && !(fda->shouldClose()))
					_acceptFDs(i);
				else if (_fds[i].revents & POLLIN && !(fda->shouldClose()))
					_read(i);
				else if (_fds[i].revents & POLLOUT && !(fda->shouldClose()))
					_write(i);
				if (fda->shouldClose())
				{
					_closeFD(i);
					i = 0;
				}
			}
		}
		else
		{
			Debug("Poll timed out", DBG_DEV);
			for (size_t i = 0; i < _fds.size(); i++)
			{
				fda = &(_fds.getAttr(i));
				if (fda->getKind() != FDKIND_SOCKET)
				{
					if (fda->oneShot())
					{
						fda->completedContent(true);
						fda->oneShot(false);
						__checkSendReady(i);
					}
					else if (fda->cgiReady().isSet()) // there is a cgi. check if it is completed.
						__checkSendReady(i);
					if (fda->shouldClose())
					{
						_closeFD(i);
						i = 0;
					}
				}
			}

		}
	}
}

void WebServer::_signalHandler( int signal )
{
	Debug("Interrupt Signal Received: " + ft::to_string(signal) + "... Closing Server.", DBG_WARNING);
	for (std::vector<WebServer *>::iterator it = WebServer::_instances.begin(); it !=  WebServer::_instances.end(); it++)
		(*it)->closeSockets();
	_stop_server = true;
}

void WebServer::closeSockets(void)
{
	for (bind_type::iterator it = _binds.begin(); it !=  _binds.end(); it++)
		close(it->getSockedFD());
}
