/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDescriptors.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:24:05 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/22 11:46:10 by iwillens         ###   ########.fr       */
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
# include "Server.hpp"

class FileDescriptors
{
	public:
		FileDescriptors(Server *srv = 0x0): server(srv) { }
		FileDescriptors(FileDescriptors const &cp) { *this = cp; }
		FileDescriptors &operator=(FileDescriptors const &cp)
		{
			clients = cp.clients;
			channels = cp.channels;
			server = cp.server;
			_fds = cp._fds;
			return (*this);
		}
		virtual ~FileDescriptors() { _fds.clear(); };
		std::map<int, Client>				clients;
		std::map<std::string, Channel>		channels;
		Server								*server;

	private:
		std::vector<pollfd>					_fds;
		
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


		void disconnect_client(Client *client)
		{
			Commands("QUIT :" + client->get_hangup_message(), client, &clients, &channels, server);
			for (std::map<std::string, Channel>::iterator chanit = channels.begin(); chanit != channels.end(); chanit++)
				chanit->second.remove_user(client->nickname);
			/*
			** here we should disconnect the user entirely from the channels
			** so more functions may be called.
			*/

			/*
			** also here, we add the client to the WHOWAS list.
			*/
		}

		/*
		** removes any fd that has been queued for removal.
		** A HANGUP generates an error message to the user and
		** informs everyone that shares a channel with them.
		** The hangup user message is created at the moment that client hangup
		** is set to be true.
		** The message to the others users are sent in the remove_queued()
		** function
		*/

		void remove_queued()
		{
			std::map<int,Client>::iterator prev;
            for (std::map<int,Client>::iterator it = clients.begin(); it != clients.end(); )
			{
				
				if (it->second.get_hangup())
				{
					prev = it++;
					disconnect_client(&(prev->second));
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
					Commands(*msg_it, &(it->second), &clients, &channels, server);
					msg_it = it->second.get_receive_queue().erase(msg_it);
				}
			}
//			remove_queued(); // calls remove queue again in case anyone was added for hangup during commands processing.
		}

		void pingpong(void)
		{
			time_t now = time(NULL);

		   	for (std::map<int,Client>::iterator it = ++clients.begin(); it != clients.end(); it++)
			{
				if (it->second.registered)
				{
					if (it->second.is_ping == false && now - it->second.last_ping > (SRV_PINGWAIT))
					{
						it->second.get_send_queue().push_back("PING " + it->second.nickname + "\r\n"); // NOt the definitive form
						it->second.is_ping = true;
					}
					else if (it->second.is_ping == true && now - it->second.last_ping > (SRV_PINGWAIT + SRV_PONGWAIT))
					{
						Debug("HANGUP", DBG_WARNING);
						std::map<std::string, std::string> v;
						v["nickname"] = it->second.nickname;
						v["server"] = server->servername();
						it->second.set_hangup(true, Commands::generate_errormsg(ERR_PINGTIMEOUT, v));
					}
				}
				else if (now - it->second.joined_time > (SRV_REGISTERWAIT))
				{
					Debug("HANGUP", DBG_WARNING);
					std::map<std::string, std::string> v;
					v["nickname"] = it->second.nickname;
					v["server"] = server->servername();
					it->second.set_hangup(true, Commands::generate_errormsg(ERR_REGISTERTIMEOUT, v));
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
