/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:36:18 by romanbtt          #+#    #+#             */
/*   Updated: 2022/02/22 22:41:02 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include "Debug.hpp"

Socket::Socket( void )
{
	return;
}

Socket::Socket( int port )
{
	_port = port;
	_create_socket();
	_bind_socket();
	_listen_socket();
}

Socket::Socket(Socket const &cp) { *this = cp; }

Socket::~Socket( void )
{
	return ;
}

Socket &Socket::operator=( const Socket& rhs )
{
	if (this != &rhs)
	{
		std::memset(&_server_address, 0, sizeof(_server_address));
		_server_socket = rhs._server_socket;
		_server_address.sin6_family = rhs._server_address.sin6_family;
		_server_address.sin6_port = rhs._server_address.sin6_port;
		_server_address.sin6_addr = rhs._server_address.sin6_addr;
	}
	return (*this);
}

void	Socket::_create_socket( void )
{
	_server_socket = socket(PF_INET6, SOCK_STREAM | SOCK_NONBLOCK, 0);
	int enable = 1;
	setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	if (_server_socket == -1)
		throw std::runtime_error("Unable to create socket.");
	return ;
}

/*
** reference for ADDR + PORT reuse.
** https://stackoverflow.com/questions/14388706/how-do-so-reuseaddr-and-so-reuseport-differ
*/
void	Socket::_bind_socket( void )
{
	int ret;

	std::memset(&_server_address, 0, sizeof(_server_address));
	_server_address.sin6_family = AF_INET6;
	_server_address.sin6_port = htons(_port);
	_server_address.sin6_addr = in6addr_any;

	ret = bind(_server_socket, (struct sockaddr *)&_server_address, sizeof(_server_address));
	if (ret == -1)
	{
		throw std::runtime_error("Port unavailable.");
		return ;
	}	
}

void	Socket::_listen_socket( void )
{
	int ret;
	
	ret = listen(_server_socket, SOMAXCONN);
	if (ret == -1)
	{
		throw std::runtime_error("Unable to listen on socket.");
		return ;
	}	
}

int	Socket::get_server_socket( void ) const
{
	return _server_socket;
}
