/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:07:16 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/12 15:04:02 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP


# include <map>
# include <string>
# include "Client.hpp"
# include "Channel.hpp"
/*
** the command Class parses the command, creates a response, and sends it to the appropriate clients.
*/

class Commands
{
	public:
		Commands(std::string command, Client &sender, std::map<int, Client> &clients): _command(command), _sender(sender), _clients(clients) { }
		Commands(Commands const &cp): _sender(cp._sender), _clients(cp._clients) { *this = cp; }
		Commands &operator=(Commands const &cp)
		{
			_sender = cp._sender;
			_clients = cp._clients;
			_command = cp._command;
			return (*this);
		}
		virtual ~Commands() { };
	
	private:
		Commands(void);
		std::string						_command;
		Client							&_sender;
		std::map<int, Client>			&_clients;
//		std::map<std::string, Channel>	&_channels;

		void	_process()
		{
			std::vector<std::string> cmd = ft::split(_command, " ");
			if (cmd.front() == "NICK")
				_sender.get_send_queue().push_back("");
		}

		Client *_get_client_by_nickname(std::string nick)
		{
			for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++ )
				if (it->second.nickname == nick)
					return (&(it->second));
			return (NULL);
		}
		
	public:



};

#endif
