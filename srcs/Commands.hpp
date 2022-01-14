/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:07:16 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/13 20:20:44 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP


# include <map>
# include <vector>
# include <string>
# include <algorithm>
# include "Debug.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "utilities.hpp"

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
		std::vector<std::string>		_parsed_command;
		Client							&_sender;
		std::map<int, Client>			&_clients;

		typedef  void (Commands::*cmd_type)(void);
		static std::map<std::string, cmd_type> initFunction(void);
		static std::map<std::string, cmd_type> _commands;

		/*
		** command helpers
		*/
		Client *_get_client_by_nickname(std::string nick)
		{
			for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++ )
				if (it->second.nickname == nick)
					return (&(it->second));
			return (NULL);
		}

		/*
		** command parsing and processing
		*/

		void	_process()
		{
			_parsed_command = ft::split(_command, " ");
			_parsed_command.push_back(_command);
			ft::uppercase(_parsed_command.front());
			_run_command(_parsed_command.front());
		}

		void _run_command(std::string &cmd_name)
		{
			std::map<std::string, cmd_type>::iterator cmd_it;
			Debug("Looking for command", DBG_DEV);

			cmd_it = _commands.find(cmd_name);
			if (cmd_it == _commands.end())
				_cmd_unknown();
			else
				(*this.*(cmd_it->second))();
		}

		/*
		** IRC Commands
		*/

		void _cmd_nick(void)
		{
			std::string old_nick = _sender.nickname;
			_sender.nickname = _parsed_command.back();
			if (_sender.registered)
				_sender.get_send_queue().push_back(":" + old_nick + " NICK " + _sender.nickname + "\r\n"); // send message that user changed nickname.
			else if (!(_sender.realname.empty()))
			{
				_sender.registered = true;
				_sender.get_send_queue().push_back(":server 001  " + _sender.nickname + "!" + _sender.realname + "@server\r\n"); // PERFORM WELCOME
				_cmd_motd();
			}			
		}
		
		void _cmd_user(void)
		{
			if (_sender.registered)
				_sender.get_send_queue().push_back(""); // reply already registered
			else
			{
				_sender.realname = _parsed_command.back();
				if (!(_sender.nickname.empty()))
				{
					_sender.registered = true;
					_sender.get_send_queue().push_back(":server 001  " + _sender.nickname + "!" + _sender.realname + "@server\r\n"); // PERFORM WELCOME
					_cmd_motd();
				}
			}

		}

		void _cmd_motd(void)
		{
			_sender.get_send_queue().push_back(":server 375  " + _sender.nickname + " :- Message of the day - \r\n"); // PERFORM WELCOME
			_sender.get_send_queue().push_back(":server 372  " + _sender.nickname + " :THIS IS THE MESSAGE OF THE DAY\r\n"); // 
			_sender.get_send_queue().push_back(":server 376  " + _sender.nickname + " :End of /MOTD command\r\n"); // 	
		}

		void _cmd_pong(void)
		{
			_sender.get_send_queue().push_back(":server 375  " + _sender.nickname + " :- Message of the day - \r\n"); // PERFORM WELCOME
			_sender.get_send_queue().push_back(":server 372  " + _sender.nickname + " :THIS IS THE MESSAGE OF THE DAY\r\n"); // 
			_sender.get_send_queue().push_back(":server 376  " + _sender.nickname + " :End of /MOTD command\r\n"); // 	
		}

		void _cmd_unknown(void)
		{
			Debug("Unknown Command");
			_sender.get_send_queue().push_back(":server 421  " + _parsed_command.front() + " :Unknown command\r\n"); // 	
		}

};

#endif
