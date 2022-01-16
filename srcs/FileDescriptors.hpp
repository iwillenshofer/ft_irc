/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDescriptors.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:24:05 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/15 20:25:46 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEDESCRIPTORS_HPP
# define FILEDESCRIPTORS_HPP

# include "Debug.hpp"
# include "Client.hpp"
# include <poll.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include "Commands.hpp"

class FileDescriptors
{
	public:
		FileDescriptors() { }
		FileDescriptors(FileDescriptors const &cp) { *this = cp; }
		FileDescriptors &operator=(FileDescriptors const &cp)
		{
			_fds = cp._fds;
			return (*this);
		}
		virtual ~FileDescriptors() { _fds.clear(); };
		std::map<int, Client>				clients;
		std::map<std::string, Channel>		channels;

	private:
		std::vector<pollfd>					_fds;
		
//		char						_buffer[BUFFERSIZE + 1];

	public:

		/*
		** getters & setters
		*/

		int	get_fd(size_t idx) { return (_fds[idx].fd); }
		int	get_revents(size_t idx) { return (_fds[idx].revents); }
		int	get_events(size_t idx) { return (_fds[idx].events); }
		void set_events(size_t idx, int events) { _fds[idx].events = events; }

//		char *get_buffer()
//		{
//			return ( _buffer );
//		}
		
		size_t size() { return (_fds.size()); }

		/*
		** adds an element (fd) to the pollfd.
		** element 0 is always the Socket.
		** non blocking fd is set here.
		*/

		void add(int fd)
		{
			pollfd tmp;

			fcntl(fd, F_SETFL, O_NONBLOCK);
			tmp.fd = fd;
			tmp.events = POLLIN;
			tmp.revents = 0x0;
			clients[fd].set_fd(fd);
			clients[fd].set_hangup(false);
			_fds.push_back(tmp);
		}

		/*
		** removes an fd from the poll.
		*/

		void remove(int fd)
		{
			std::vector<pollfd>::iterator it = _fds.begin();

			close(fd);
			while (it != _fds.end())
			{
				if (it->fd == fd)
				{
					it = _fds.erase(it);
					return ;
				}
				it++;
			}
		}

		/*
		** returns a list of the polled fds, to be used by poll().
		** before returning, checks if there's anything to be written to a client
		** and, if there is, sets POLLOUT.
		*/
	
		pollfd *list(void)
		{
			for (std::vector<pollfd>::iterator it = _fds.begin(); it != _fds.end(); it++)
			{
				if (clients[it->fd].get_send_queue_size())
					it->events = POLLOUT;
				else
					it->events = POLLIN;
			}
			if (_fds.size())
				return (&(_fds.at(0)));
			return (0x0);
		}

		/*
		** removes any fd that has been queued for removal.
		*/

		void remove_queued()
		{
			std::map<int,Client>::iterator prev;
            for (std::map<int,Client>::iterator it = clients.begin(); it != clients.end(); )
			{
				if (it->second.get_hangup())
				{
					prev = it++;
					Debug("FD to Remove: " + ft::to_string(prev->second.get_fd()), DBG_ERROR);
					remove(prev->second.get_fd());
					clients.erase(prev);
					Debug("Clients size: " + ft::to_string(clients.size()) + "FDS size: " + ft::to_string(_fds.size()), DBG_ERROR);
				}
				else
					it++;
			}
		}
		
		void process_commands(void)
		{
			/*
			** here all the commands (inputs) will be processed
			** setting any channel/user property and adding any
			** return message into the clients' queue.
			** it will be a loop going through all of the client's received messages.
			**
			** Maybe we could create a Commands class, which would receive a pointer to
			** the classes Channel, User and Client, to do the appropriate changes in any of them.
			** The Commands class would be also a parser.
			** if the command is invalid, it adds a message to the client's send queue.
			** if the command is valid, it process it and also adds the returning message to the clients' queue.
			** I'm not sure if we need a User class yet, as the client class may be enough.
			*/
		    for (std::map<int,Client>::iterator it = clients.begin(); it != clients.end(); it++)
			{
				for (std::vector<std::string>::iterator msg_it = it->second.get_receive_queue().begin(); msg_it != it->second.get_receive_queue().end();)
				{
					Commands(*msg_it, it->second, clients, channels);
					msg_it = it->second.get_receive_queue().erase(msg_it);
				}
			}
		}

		void pingpong(void)
		{
			time_t now = time(NULL);

		   	for (std::map<int,Client>::iterator it = ++clients.begin(); it != clients.end(); it++)
			{
				if (it->second.is_ping == false && now - it->second.last_ping > 7)
				{
					it->second.get_send_queue().push_back("PING " + it->second.nickname + "\r\n"); // NOt the definitive form
					it->second.is_ping = true;
				}
				else if (it->second.is_ping == true && now - it->second.last_ping > 10)
				{
					Debug("HANGUP", DBG_WARNING);
					it->second.set_hangup(true);
				}			
			}
			
			/*
			** here we will check ping commands sent to the clients when idle
			** to make sure it is active.
			** if not, it will close the connection (by marking the client.hangup = true)
			*/
		}
};

#endif
