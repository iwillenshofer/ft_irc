/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:40:08 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/09 09:46:56 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <vector>
# include <csignal>
# include "Socket.hpp"
# include "FileDescriptors.hpp"
# include "Debug.hpp"

class WebServer
{
	public:

		public:
			/*
			** Coplien Form
			*/
			WebServer(int port);
			WebServer(WebServer const &cp);
			WebServer &operator=(WebServer const &cp);
			virtual ~WebServer();


		private:
			Socket							_socket;
			FileDescriptors 				_clients;
			static std::vector<WebServer *> _instances; // instances of self to be used in SignalHandler
			static bool 					_stop_server; 	// instances of self to be used in SignalHandler
			
			void			_init(std::string configfile);
			static void 	_signalHandler( int signal );

		public:
			Bind *getBind(std::string ip, int port);
			Bind *getBind(int fd);
			void closeSockets(void);
			bool isBindFd(int fd);
			void _initializeFDs(void);
			void _acceptFDs(int fd);
			void _checkFdError(int fd);
			void _read(int fd);
			void _write(int fd);
			void _closeFD(int fd);
			void __setHeader(int fd);
			void __checkCompleteContent(int fd);
			void __checkKernelAvailable(int fd);
			void __checkSendReady(int fd);

			size_t __getBufferSize(int fd);

			void RunServer(void);
			void print(void);
};

#endif
