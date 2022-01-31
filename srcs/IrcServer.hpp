/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:40:08 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/31 14:20:41 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <vector>
# include <map>
# include <csignal>
# include <cerrno>
# include "Socket.hpp"
# include "Server.hpp"
# include "Connections.hpp"
# include "Debug.hpp"
# include <poll.h>
# include <fcntl.h>
 #include <sys/ioctl.h>
 #include <unistd.h>
 
class IrcServer
{
	public:

		public:
			/*
			** Coplien Form
			*/
			IrcServer(std::string host, int port, std::string password);
			IrcServer(IrcServer const &cp);
			IrcServer &operator=(IrcServer const &cp);
			virtual ~IrcServer();


		private:
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
			static std::vector<IrcServer *> _instances; // instances of self to be used in SignalHandler
			static bool 					_stop_server; 	// instances of self to be used in SignalHandler
			static void 	_signalHandler( int signal );

		public:
			void _accept_connections(int fd);
			void _close_all_connections(void);
			void RunServer(void);
			void print(void);
};

#endif
