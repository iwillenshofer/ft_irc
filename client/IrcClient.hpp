/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:55:35 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/17 22:16:28 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCLIENT_HPP
# define IRCCLIENT_HPP

# include <string>
# include <vector>
# include <poll.h>
# include <fcntl.h>
# include <signal.h>
# include "Debug.hpp"
# include "Mask.hpp"
# include "utilities.hpp"
# include "server_defaults.hpp"
# include "Message.hpp"
#include <ctime>
# include <climits>
# define BUFFERSIZE 1024

class IrcClient
{
	public:
		IrcClient();
		IrcClient(IrcClient const &cp);
		IrcClient &operator=(IrcClient const &cp);
		virtual ~IrcClient();
	
	private:
		int									_fd;
		struct sockaddr_in					_server_address;
	    struct hostent						*server;
		char								_buffer[BUFFERSIZE + 1];
		std::string							_receive_buffer;
		std::string							_send_buffer;
		std::vector<std::string> 			_receive_queue;
		std::vector<std::string> 			_send_queue;
		int									_port;
		std::string							_server;

	public:
		std::string 						_nickname;
		std::string 						_username;
		std::string 						_hostname;
		std::string 						_realname;
		std::string							_password;
		bool								_registered;
		bool								_register_sent;
		bool								_joined;
		static std::vector<std::string>		_chats;
		static std::vector<std::string>		_nicknames;

		/*
		** variables and functions for signal handler.
		*/
		static std::vector<IrcClient *> _instances;
		static bool 					_stop_clients;
		static void 	_signalHandler( int signal );


		static std::vector<std::string> init_chats(void);
		static std::vector<std::string> init_nicknames(void);
		std::string get_random(std::vector<std::string>&v);


		/*
		** reads messages from the client. If message is incomplete,
		** it is kept on buffer to be read on the next poll loop.
		*/

		void create_socket( void );
		void connect_socket( std::string server, int port, std::string password);
		void runClient(void);
		void registerClient (void);
		void processCommands (void);
		void joinChannel (void);
		void sendMessage(void);
		void read(void);
		void write(void);
};

#endif
