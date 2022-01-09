/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:55:35 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/09 17:55:34 by iwillens         ###   ########.fr       */
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
		size_t get_send_queue_size(void) { return (_send_queue.size()); }
		bool get_hangup(void) { return (_hangup); }
		void set_hangup(bool v) { _hangup = v; }
		int get_fd(void) { return (_fd); }
		void set_fd(int fd) { _fd = fd; }
		void print()
		{
			Debug("Fd: " + ft::to_string(_fd) + " HUP:" + (_hangup == true?"true":"false"), DBG_WARNING);
		}

		void read(void)
		{
			std::vector<std::string> tmp;

			bzero(_buffer, BUFFERSIZE + 1);
			ssize_t rc = recv( _fd, _buffer, BUFFERSIZE, 0);
			if (rc > 0)
			{
				Debug("Tmp Size:" + ft::to_string(tmp.size()) + " Recv Size:" + ft::to_string(_receive_queue.size()));
				Debug("Read");
				_receive_buffer += _buffer;
				Debug(_receive_buffer, DBG_DEV);
				tmp = ft::split(_receive_buffer, "\r\n");
				_receive_queue.insert(_receive_queue.end(), tmp.begin(), tmp.end());
				Debug("Tmp Size:" + ft::to_string(tmp.size()) + " Recv Size:" + ft::to_string(_receive_queue.size()));
				for (std::vector<std::string>::iterator it = _receive_queue.begin(); it != _receive_queue.end(); it++)
					Debug(*it + "\n");
			}
			else if (rc <= 0)
			{ 
				// rc == 0 other side closed socket 
				// rc == -1 error;
			}
		}

		void write(void)
		{
			
			//	int rc;
			//
			//	rc = send(_clients[fd_idx].fd, _clients.getContent(fd_idx), _clients.getContentSize(fd_idx), 0);
			//	if (rc == -1)
			//		std::cerr << "Error send" << std::endl;
			//	_clients.getAttr(fd_idx).shouldClose(true);
		}



};

#endif
