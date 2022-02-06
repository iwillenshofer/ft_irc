/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:24:00 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/06 16:12:21 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connections.hpp"

Connections::Connections(Server *srv): server(srv) { }
Connections::Connections(Connections const &cp) { *this = cp; }

Connections & Connections::operator=(Connections const &cp)
{
	clients = cp.clients;
	channels = cp.channels;
	server = cp.server;
	_fds = cp._fds;
	return (*this);
}

Connections::~Connections() { _fds.clear(); }

/*
** getters & setters
*/

int		Connections::get_fd(size_t idx) { return (_fds[idx].fd); }
int		Connections::get_revents(size_t idx) { return (_fds[idx].revents); }
int		Connections::get_events(size_t idx) { return (_fds[idx].events); }
void	Connections::set_events(size_t idx, int events) { _fds[idx].events = events; }
size_t	Connections::size() { return (_fds.size()); }

/*
** adds an element (fd) to the pollfd.
** element 0 is always the Socket.
** non blocking fd is set here.
*/

void	Connections::add(int fd)
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

void	Connections::remove(int fd)
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

pollfd	*Connections::list(void)
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

void	Connections::disconnect_client(Client *client)
{
	std::map<std::string, Channel>::iterator tmp;
	Commands("QUIT :" + client->get_hangup_message(), client, &clients, &channels, server);
	for (std::map<std::string, Channel>::iterator chanit = channels.begin(); chanit != channels.end(); )
	{
		chanit->second.remove_user(*client);
		if (chanit->second.is_empty())
		{
			tmp = chanit;
			tmp++;
			channels.erase(chanit);
			chanit = tmp;
		}
		else
			chanit++;
	}
	server->add_whowas(*client);
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

void	Connections::remove_queued()
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

void	Connections::process_commands(void)
{
	for (std::map<int,Client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		for (std::vector<std::string>::iterator msg_it = it->second.get_receive_queue().begin(); msg_it != it->second.get_receive_queue().end();)
		{
			Commands(*msg_it, &(it->second), &clients, &channels, server);
			msg_it = it->second.get_receive_queue().erase(msg_it);
		}
	}
}

void	Connections::pingpong(void)
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
				it->second.set_hangup(true, Commands::generate_errormsg(ERR_PINGTIMEOUT));
			}
		}
		else if (now - it->second.joined_time > (SRV_REGISTERWAIT))
		{
			Debug("HANGUP", DBG_WARNING);
			it->second.set_hangup(true, Commands::generate_errormsg(ERR_REGISTERTIMEOUT));
		}
	}
}
