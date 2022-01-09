/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:36:18 by romanbtt          #+#    #+#             */
/*   Updated: 2022/01/09 09:18:52 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket( void )
{
	return;
	// do nothing at all. Will need to be replaced
	// by a socket with argument.
	_port = 80;
	_create_socket();
	_bind_socket();
	_listen_socket();
}

Socket::Socket( int port )
{
	_port = port;
	_create_socket();
	_bind_socket();
	_listen_socket();
}

Socket::Socket( config_data config )
{
	_port = config.port;
	_create_socket();
	_bind_socket();
	_listen_socket();
}

Socket::~Socket( void )
{
	return ;
}

Socket &Socket::operator=( const Socket& rhs )
{
	if (this != &rhs)
	{
		_server_socket = rhs._server_socket;
		_server_address.sin_family = rhs._server_address.sin_family;
		_server_address.sin_port = rhs._server_address.sin_port;
		_server_address.sin_addr.s_addr = rhs._server_address.sin_addr.s_addr;
		std::memset(_server_address.sin_zero, '\0', sizeof(_server_address.sin_zero));
	}
	return (*this);
}

// Create a server socket

void	Socket::_create_socket( void )
{
	// PF_INET = IPV4; SOCK_STREAM = TCP; Protocol set to 0, to let the function 
	// choose the proper protocol for the given type
	_server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (_server_socket == -1)
	{
		return ;
		// TO DO: Print Error, Errno is set appropriately.
	}
}

void	Socket::_bind_socket( void )
{
	int ret;
	
	_server_address.sin_family = AF_INET; // Family IPV4
	_server_address.sin_port = htons(_port); // Port to listen
	_server_address.sin_addr.s_addr = INADDR_ANY; // Listen all IP incoming
	std::memset(_server_address.sin_zero, '\0', sizeof(_server_address.sin_zero));

	ret = bind(_server_socket, (struct sockaddr *)&_server_address, sizeof(_server_address));
	if (ret == -1)
	{
		return ;
		// TO DO: Print Error, Errno is set appropriately.
	}	
}

void	Socket::_listen_socket( void )
{
	int ret;
	
	ret = listen(_server_socket, SOMAXCONN);
	if (ret == -1)
	{
		return ;
		// TO DO: Print Error, Errno is set appropriately.
	}	
}

int	Socket::get_server_socket( void ) const
{
	return _server_socket;
}
