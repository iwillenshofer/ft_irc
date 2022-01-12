/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:55:35 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/11 19:51:32 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# define BUFFERSIZE 1024

class Client
{
	public:
		Client(int fd = 0): _fd(fd), _hangup(false) { }
		Client(Client const &cp) { *this = cp; }
		Client &operator=(Client const &cp)
		{
			_fd = cp._fd;
			_receive_buffer = cp._receive_buffer;
			_send_buffer = cp._send_buffer;
			_receive_queue = cp._receive_queue;
			_send_queue = cp._send_queue;
			_hangup = cp._hangup;
			return (*this);
		}
		virtual ~Client() { };
	
	private:
		int							_fd;
		char						_buffer[BUFFERSIZE + 1];
		std::string					_receive_buffer;
		std::string					_send_buffer;
		std::vector<std::string> 	_receive_queue;
		std::vector<std::string> 	_send_queue;
		bool						_hangup;
	
	public:
		/*
		** setters and getters.
		*/

		size_t get_send_queue_size(void) { return (_send_queue.size()); }
		bool get_hangup(void) { return (_hangup); }
		void set_hangup(bool v) { _hangup = v; }
		int get_fd(void) { return (_fd); }
		void set_fd(int fd) { _fd = fd; }
		
		/*
		** reads messages from the client. If message is incomplete,
		** it is kept on buffer to be read on the next poll loop.
		*/

		void read(void)
		{
			std::vector<std::string> tmp;
			Debug("Read", DBG_DEV);
			bzero(_buffer, BUFFERSIZE + 1);
			ssize_t rc = recv( _fd, _buffer, BUFFERSIZE, 0);
			if (rc > 0)
			{
				_receive_buffer += _buffer;
				tmp = ft::split(_receive_buffer, "\r\n");
				_receive_queue.insert(_receive_queue.end(), tmp.begin(), tmp.end());
				for (std::vector<std::string>::iterator it = _receive_queue.begin(); it != _receive_queue.end(); it++)
					Debug(*it + "\n");
		
				//just a test
				_send_queue.push_back(":localhost 001 asdasds : Olá\r\n");
			}
			else if (rc <= 0)
			{ 
				// rc == 0 other side closed socket 
				// rc == -1 error;
				/*
				** kept for comments only, we will remove this.
				** We don't care for sending errors or client hangup:
				** if there's an error, the message is still there to be sent.
				** if the client hungup, it will be catched by the ping pong loop.
				*/
			}
		}

		/*
		** writes any queued message to client.
		** if message if not fully sent, its remaining is kept on queue to be sent on
		** the next loop.
		*/
	
		void write(void)
		{
			int rc;
			Debug("Write", DBG_DEV);
			if (!(_send_queue.size()))
				return;
			rc = send(_fd, _send_queue.at(0).c_str(), _send_queue.at(0).size(), 0);
			if (rc > 0)
			{
				_send_queue.at(0).erase(0, rc);
				if (!(_send_queue.at(0).size()))
					_send_queue.erase(_send_queue.begin());
			}
		}
};

#endif
