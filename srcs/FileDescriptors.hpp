/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDescriptors.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:24:05 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/09 17:30:15 by iwillens         ###   ########.fr       */
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
		
		char						_buffer[BUFFERSIZE + 1];

	public:
		size_t size() { return (_fds.size()); }

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

		int	get_fd(size_t idx) { return (_fds[idx].fd); }
		int	get_revents(size_t idx) { return (_fds[idx].revents); }
		int	get_events(size_t idx) { return (_fds[idx].events); }
		void set_events(size_t idx, int events) { _fds[idx].events = events; }

		char *get_buffer()
		{
			return ( _buffer );
		}

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
};

#endif
