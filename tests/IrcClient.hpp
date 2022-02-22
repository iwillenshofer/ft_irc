/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:55:35 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/19 21:18:39 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCLIENT_HPP
# define IRCCLIENT_HPP

# include <string>
# include <vector>
# include <fcntl.h>
# include <ctime>
# include <climits>
# include <unistd.h>
# include "Mask.hpp"
# include "Message.hpp"
# include "Debug.hpp"
# include "utilities.hpp"
# include "server_defaults.hpp"

# define LOG_SEND 0
# define LOG_RECV 1
# define READ_WAIT_TIME 150000

class IrcClient
{
	public:
		IrcClient(void);
		IrcClient(std::string address, int port);
		IrcClient(IrcClient const &cp);
		IrcClient &operator=(IrcClient const &cp);
		virtual ~IrcClient();
	
	private:
		int									_fd;
		int									_port;
		std::string							_address;
		char								_buffer[BUFFERSIZE + 1];
		std::string							_receive_buffer;
		std::string							_send_buffer;
		std::vector<std::string> 			_receive_queue;
		std::vector<std::string> 			_send_queue;
		static int							_instances_count;
		int									_instance;
		bool								_connected;
		/*
		** reads messages from the client. If message is incomplete,
		** it is kept on buffer to be read on the next poll loop.
		*/

		void _create_socket( void );
		void _read(bool verbose);
		void _write(bool verbose);
		void _start();
		void _log(std::string s, bool kind, bool output = true);
		std::string _log_color();

		public:
		void command(std::string command, bool verbose = true);
		void listen(bool verbose = true, int rate = READ_WAIT_TIME);
		void end(void);
		bool is_connected(void);

};

#endif
