/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:40:08 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/21 21:21:08 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <vector>
# include <map>
# include <csignal>
# include <cerrno>
# include "Socket.hpp"
# include "Server.hpp"
# include "FileDescriptors.hpp"
# include "Debug.hpp"
# include <poll.h>
# include <fcntl.h>
 #include <sys/ioctl.h>
 #include <unistd.h>
 
class WebServer
{
	public:

		public:
			/*
			** Coplien Form
			*/
			WebServer(std::string host, int port, std::string password);
			WebServer(WebServer const &cp);
			WebServer &operator=(WebServer const &cp);
			virtual ~WebServer();


		private:
			/*
			** private member functions and variables
			*/
			Socket							_socket;
			FileDescriptors		 			_connections;
			Server							_server;
			void							_init(int port);

			/*
			** variables and functions for signal handler.
			*/
			static std::vector<WebServer *> _instances; // instances of self to be used in SignalHandler
			static bool 					_stop_server; 	// instances of self to be used in SignalHandler
			static void 	_signalHandler( int signal );

		public:
			void _accept_connections(int fd);
			void _close_all_connections(void);
			void RunServer(void);
			void print(void);
};

#endif
