/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:35:23 by romanbtt          #+#    #+#             */
/*   Updated: 2022/02/17 21:29:57 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_H
# define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

struct config_data
{
	int	port;
};

class Socket
{
	private:
		int						_server_socket;		//	Socket FD
		struct sockaddr_in6		_server_address;	// sockaddr_in contains Port and Address where server listen to.
		int						_port;

		void _create_socket( void );
		void _bind_socket( void );
		void _listen_socket( void );	

	public:
		Socket( void );
		Socket( int port );
		Socket(Socket const &cp);
		virtual ~Socket( void );

		Socket &operator=( const Socket& rhs );
		int	get_server_socket( void ) const;
};

#endif
