/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:07:16 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/12 21:59:15 by iwillens         ###   ########.fr       */
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
		Commands(std::string command, Client &sender, std::map<int, Client> &clients): _command(command), _sender(sender), _clients(clients)
		{ _process(); }
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
			cmd.push_back(_command);
			
			if (cmd.front() == "NICK")
			{
				std::string old_nick = _sender.nickname;
				_sender.nickname = cmd.back();
				if (_sender.registered)
					_sender.get_send_queue().push_back(":" + old_nick + " NICK " + _sender.nickname + "\r\n"); // send message that user changed nickname.
				else if (!(_sender.realname.empty()))
				{
					_sender.registered = true;
					_sender.get_send_queue().push_back(":server 001  " + _sender.nickname + "!" + _sender.realname + "@server\r\n"); // PERFORM WELCOME
					_sender.get_send_queue().push_back(":server 375  " + _sender.nickname + " :- Message of the day - \r\n"); // PERFORM WELCOME
					_sender.get_send_queue().push_back(":server 372  " + _sender.nickname + " :THIS IS THE MESSAGE OF THE DAY\r\n"); // 
					_sender.get_send_queue().push_back(":server 376  " + _sender.nickname + " :End of /MOTD command\r\n"); // 
				}
			}
			else if (cmd.front() == "USER")
			{
				if (_sender.registered)
					_sender.get_send_queue().push_back(""); // reply already registered
				else
				{
					_sender.realname = cmd.back();
					if (!(_sender.nickname.empty()))
					{
						_sender.registered = true;
						_sender.get_send_queue().push_back(":server 001  " + _sender.nickname + "!" + _sender.realname + "@server\r\n"); // PERFORM WELCOME
						_sender.get_send_queue().push_back(":server 375  " + _sender.nickname + " :- Message of the day - \r\n"); // PERFORM WELCOME
						_sender.get_send_queue().push_back(":server 372  " + _sender.nickname + " :THIS IS THE MESSAGE OF THE DAY\r\n"); // 
						_sender.get_send_queue().push_back(":server 376  " + _sender.nickname + " :End of /MOTD command\r\n"); // 
					}
				}
			}
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
