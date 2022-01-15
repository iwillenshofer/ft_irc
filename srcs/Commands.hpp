/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:07:16 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/15 09:47:46 by iwillens         ###   ########.fr       */
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
# include "server_defaults.hpp"

class Message
{
	public:
		Message(std::string message): _message(message) { }
		Message(Message const &cp) { *this = cp; }
		Message &operator=(Message const &cp)
		{
			_message = cp._message;
			_prefix = cp._prefix;
			_command = cp._command;
			return (*this);
		}
		virtual ~Message() { };
	
	
	private:
		Message(void);
		std::string						_message;
		std::string						_prefix;
		std::string						_command;
		std::vector<std::string>		_arguments;

	public:
		void disassemble(void)
		{
			std::string user_message;

			if (!_message.size())
				return;
			if (_message[0] == ':')
			{
				_prefix = _message.substr(0, _message.find(' '));
				_message.erase(0, _prefix.size());
				_prefix.erase(_prefix.begin());
				_message = ft::trim(_message);
			}
			if (_message.find(" :") != _message.npos)
			{
				user_message = _message.substr(_message.find(" :"), _message.size());
				_message.erase(_message.size() - user_message.size());
				user_message.erase(0, 1);
			}
			_message = ft::trim(_message);
			_arguments = ft::split(_message, ' ');
			if (_arguments.size())
			{
				_command = _arguments[0];
				_arguments.erase(_arguments.begin());
			}
			_arguments.push_back(user_message);


		}

		void print(void)
		{
			std::string args;
			
			for (std::vector<std::string>::iterator it = _arguments.begin(); it != _arguments.end(); it++)
				args = args + "'" + *it + "'" + (it != _arguments.end() - 1 ? "," : "");
				
			Debug("_message: " + _message);
			Debug("_prefix: " + _prefix);
			Debug("_command: " + _command);
			Debug("_arguments: [" + args + "]");
		}
};



/*
** the command Class parses the command, creates a response,
** and adds it to the appropriate clients send queue.
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
		static std::map<std::string, cmd_type> init_commands(void);
		static std::map<std::string, cmd_type> _commands;
		static std::map<int, std::string> init_replies(void);
		static std::map<int, std::string> _replies;
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
		** reply generation
		*/
		std::string _numeric_reply(int reply)
		{
			std::string nb = std::to_string(reply);

			while (nb.size() < 3)
				nb.insert(nb.begin(), '0');
			return (nb);
		}

		std::string _generate_reply(int reply, std::map<std::string, std::string> v = std::map<std::string, std::string>())
		{
			std::string message = _numeric_reply(reply) + " " + _sender.nickname + " ";
			if (v.size())
				message += _replace_tags(_replies[reply], v);
			else
				message += _replies[reply];
			message += MSG_ENDLINE;
			return (message);
			(void)v;
		}

		std::string _replace_tags(std::string msg, std::map<std::string, std::string> v)
		{
			for (std::map<std::string, std::string>::iterator it = v.begin(); it != v.end(); it++)
			{
				std::string findstr("<" + it->first + ">");
				msg.replace(msg.find(findstr), findstr.size(), it->second);
			}
			return (msg);
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
			_sender.get_send_queue().push_back(_generate_reply(RPL_MOTDSTART));
			_sender.get_send_queue().push_back(_generate_reply(RPL_MOTD));
			_sender.get_send_queue().push_back(_generate_reply(RPL_ENDOFMOTD));
		}

		void _cmd_pong(void)
		{
			_sender.is_ping = false;
			_sender.last_ping = time(NULL);
		}

		void _cmd_privmsg(void)
		{
			_sender.get_send_queue().push_back(_generate_reply(RPL_ENDOFMOTD));
		}
		
		void _cmd_unknown(void)
		{
			Debug("User " + _sender.nickname + " sent an Unknown Command: " + _parsed_command.front(), DBG_INFO);
			_sender.get_send_queue().push_back(":server 421  " + _parsed_command.front() + " :Unknown command\r\n"); // 	
		}

};

#endif
