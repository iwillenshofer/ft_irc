/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDescriptors.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:24:05 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/09 09:45:01 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEDESCRIPTORS_HPP
# define FILEDESCRIPTORS_HPP

# include <poll.h>
# include <fcntl.h>
 #include <sys/ioctl.h>

# define BUFFERSIZE 1024

class Bind;

class FileDescriptors
{
	public:
		FileDescriptors(): _fds(0x0), _size(0), _capacity(0) { }
		FileDescriptors(FileDescriptors const &cp) { *this = cp; }
		FileDescriptors &operator=(FileDescriptors const &cp)
		{
			_size = cp._size;
			_capacity = cp._capacity;
			_attributes = cp._attributes;
			_fds = new pollfd[_capacity];
			memcpy(_fds, cp._fds, sizeof(pollfd) * _size);
			return (*this);
		}
		virtual ~FileDescriptors() { clear(); };

	private:
		pollfd										*_fds;
		size_t										_size;
		size_t										_capacity;
//		std::vector<FileDescriptorAttributes>		_attributes;
		char										_buffer[BUFFERSIZE + 1];
		void	_reserve(size_t n)
		{
			pollfd		*tmp;
			if (n > _capacity)
			{
				tmp = new pollfd[n];
				memcpy(tmp, _fds, sizeof(pollfd) * _size);
				_capacity = n;
				delete [] _fds;
				_fds = tmp;
			}
		}

	public:
		pollfd &operator[](size_t idx) { return _fds[idx]; }
		void push_back(int fd, Bind *listenfd = NULL, int kind = FDKIND_SOCKET)
		{
			if (_capacity < _size + 1)
				_reserve(_size ? _size * 2 : 1);
			_fds[_size].fd = fd;
			_fds[_size].events = POLLIN;
			_fds[_size].revents = 0x0;
			fcntl(fd, F_SETFL, O_NONBLOCK);
			_size++;
//			_attributes.push_back(FileDescriptorAttributes(listenfd, kind));
		}

		size_t size() { return (_size); }

		void clear()
		{
			_size = 0;
			_capacity = 0;
			delete [] _fds;
		}
		void clearBuffer()
		{
			bzero(_buffer, BUFFERSIZE + 1);
		}

		void erase(int fd)
		{
			size_t i = 0;
		
			while(i < _size)
			{
				if (_fds[i].fd == fd)
					break;
				i++;
			}
			if (i < _size)
			{
				Debug("Connection [" + ft::to_string(fd) + "] destroyed.", DBG_DEV);
//				_attributes.erase(_attributes.begin() + i);
				_size--;
			}
			while(i < _size)
			{
				_fds[i].fd = _fds[i + 1].fd;
				_fds[i].events = _fds[i + 1].events;
				_fds[i].revents = _fds[i + 1].revents;
				i++;
			}
		}

		pollfd *findFd(int fd)
		{ 
			size_t i = 0;
			while(i < _size)
			{
				if (_fds[i].fd == fd)
					return(&_fds[i]);
				i++;
			}
			return (NULL);
		}
		
		short getEvent(int fd)
		{ 
			return(findFd(fd)->events);
		}

		pollfd *getFds() { return (_fds); }
		void print()
		{ 
			for (size_t i = 0; i < _size; i++)
			{
				std::cout << "FD: " << _fds[i].fd <<  " Events: " << _fds[i].events <<  " REvents: " << _fds[i].revents << std::endl;
			}
		}

		char *getBuffer()
		{
			return ( _buffer );
		}

		int getAvailable(int fd)
		{
			int i;

			if (ioctl(fd, FIONREAD, &i) == -1)
				return ( -1 );
			return (i);
		}
};

#endif
