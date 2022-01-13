/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDescriptors.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:24:05 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/11 21:05:44 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEDESCRIPTORS_HPP
# define FILEDESCRIPTORS_HPP

# include "Debug.hpp"
# include "Client.hpp"
# include <poll.h>
# include <fcntl.h>
 #include <sys/ioctl.h>

# define BUFFERSIZE 1024

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
		std::map<int, Client>		clients;


	private:
		std::vector<pollfd>			_fds;
		
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
					remove(prev->second.get_fd());
					clients.erase(prev);
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
		}

		void pingpong(void)
		{
		    for (std::map<int,Client>::iterator it = clients.begin(); it != clients.end(); it++)
			{
				std::string nick = it->second.nickname;
				Debug(nick, DBG_INFO);
			}
			
			/*
			** here we will check ping commands sent to the clients when idle
			** to make sure it is active.
			** if not, it will close the connection (by marking the client.hangup = true)
			*/
		}
};

#endif
