/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:24:05 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/28 09:36:43 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTIONS_HPP
# define CONNECTIONS_HPP

# include "Debug.hpp"
# include "Client.hpp"
# include <poll.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include "Commands.hpp"
# include "Server.hpp"

class Connections
{
	public:
		Connections(Server *srv = 0x0);
		Connections(Connections const &cp);
		Connections &operator=(Connections const &cp);
		virtual ~Connections();
		std::map<int, Client>				clients;
		std::map<std::string, Channel>		channels;
		Server								*server;

	private:
		std::vector<pollfd>					_fds;
		
	public:
		/*
		** getters & setters
		*/
		int	get_fd(size_t idx);
		int	get_revents(size_t idx);
		int	get_events(size_t idx);
		void set_events(size_t idx, int events);
		size_t size();

		/*
		** fd operations
		*/
		void add(int fd);
		void remove(int fd);
		pollfd *list(void);

		/*
		** client operations
		*/
		void disconnect_client(Client *client);
		void remove_queued();
		void process_commands(void);
		void pingpong(void);
};

#endif
