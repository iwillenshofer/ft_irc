/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:40:08 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/22 20:56:22 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <map>
# include <vector>
# include <csignal>
# include <poll.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include "Socket.hpp"
# include "Server.hpp"
# include "Connections.hpp"
# include "Debug.hpp"
 
class IrcServer
{
	public:

		public:
			/*
			** Coplien Form
			*/
			IrcServer(std::string host, int port, unsigned long password);
			IrcServer(IrcServer const &cp);
			IrcServer &operator=(IrcServer const &cp);
			virtual ~IrcServer();


		private:
			IrcServer();

			/*
			** private member functions and variables
			*/
			Socket							_socket;
			Connections		 				_connections;
			Server							_server;
			void							_init(int port);

			/*
			** variables and functions for signal handler.
			*/
			static std::vector<IrcServer *> _instances;
			static bool 					_stop_server;
			static void 	_signalHandler( int signal );

		public:
			void _accept_connections(int fd);
			void _close_all_connections(void);
			void RunServer(void);
			void print(void);
};

#endif
