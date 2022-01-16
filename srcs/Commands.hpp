/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:07:16 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/15 22:51:40 by iwillens         ###   ########.fr       */
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
		Message(void) {};
		Message(std::string message): _message(message) { _disassemble(); }
		Message(Message const &cp) { *this = cp; }
		Message &operator=(Message const &cp)
		{
			_message = cp._message;
			_prefix = cp._prefix;
			_command = cp._command;
			_arguments = cp._arguments;
			return (*this);
		}
		virtual ~Message() { };
	
	
	private:
		std::string						_message;
		std::string						_prefix;
		std::string						_command;
		std::vector<std::string>		_arguments;

	public:
		/*
		** getters
		*/
		std::string					&message(void) {return (_message); }
		std::string					&prefix(void) {return (_prefix); }
		std::string					&command(void) {return (_command); }
		std::vector<std::string>	&arguments(void) {return (_arguments); }
		
	private:
		/*
		** 
		*/
		void _disassemble(void)
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
	
	public:
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
		Commands(std::string message, Client &sender, std::map<int, Client> &clients, std::map<std::string, Channel> &channels): _message(message), _sender(sender), _clients(clients), _channels(channels)
		{ _process(); }
		Commands(Commands const &cp): _sender(cp._sender), _clients(cp._clients), _channels(cp._channels) { *this = cp; }
		Commands &operator=(Commands const &cp)
		{
			_sender = cp._sender;
			_clients = cp._clients;
			_message = cp._message;
			_channels = cp._channels;
			return (*this);
		}
		virtual ~Commands() { };
	
	private:
		Commands(void);
		Message							_message; // parsed command
		Client							&_sender;
		std::map<int, Client>			&_clients;
		std::map<std::string, Channel>	&_channels;


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
			_run_command(_message.command());
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
		** sends a message to all channels _sender is in
		*/
		void _message_all_channels(std::string &msg, bool sender_too)
		{
			(void)msg;(void)sender_too;			
		}

		/*
		** sends a message to a specific channel
		*/
		void _message_channel(std::string &msg, std::string &channel, bool sender_too)
		{
			for (std::vector<std::string>::iterator it = _channels[channel].users.begin(); it !=_channels[channel].users.end(); it++)
				if (*it != _sender.nickname || sender_too)
					_message_user(msg, *it);
		}

		/*
		** sends a message to a specific user
		*/
		void _message_user(std::string msg, std::string &nickname)
		{
			Client *client = _get_client_by_nickname(nickname);

			if (!(client))
				_message_user(_generate_reply(ERR_NOSUCHNICK), _sender);
			else
				_message_user(msg, *client);
		}

		void _message_user(std::string msg, Client &client)
		{
			client.get_send_queue().push_back(msg);
		}

		/*
		** IRC Commands Helpers
		*/
		void _register_user(void)
		{
			Debug("User Registered", DBG_ERROR);
			_sender.registered = true;
			_message_user(_generate_reply(RPL_WELCOME), _sender);
			_message_user(_generate_reply(RPL_YOURHOST), _sender);
			_message_user(_generate_reply(RPL_CREATED), _sender);
			_message_user(_generate_reply(RPL_MYINFO), _sender);
			_cmd_motd();
		}
		
		bool _validate_nick(std::string const &nickname) const
		{
			(void)nickname;			
			return (true);
		}

		/*
		** IRC Commands
		*/

		void _cmd_user(void)
		{
			if (_sender.registered)
				_message_user(_generate_reply(ERR_ALREADYREGISTRED), _sender);
			else if (_message.arguments().size() < 4)
				_message_user(_generate_reply(ERR_NEEDMOREPARAMS), _sender);
			else
			{
				Debug("USER");
				_sender.realname = _message.arguments()[3];
				_sender.username = _message.arguments()[0];
				_message.print();
				if (!(_sender.nickname.empty()))
					_register_user();
				else
					Debug(_sender.nickname, DBG_ERROR);
			}
		}

		void _cmd_nick(void)
		{
			std::string old_nick = _sender.nickname;
			if (_message.arguments().size() == 0 || _message.arguments()[0].empty())
				_message_user(_generate_reply(ERR_NONICKNAMEGIVEN), _sender);
			else if (_get_client_by_nickname(_message.arguments()[0]) != NULL && _sender.nickname != _message.arguments()[0])
				_message_user(_generate_reply(ERR_NICKNAMEINUSE), _sender);
			else if (!(_validate_nick(_message.arguments()[0])))
				_message_user(_generate_reply(ERR_ERRONEUSNICKNAME), _sender);
			else
			{
				Debug("NICK");
				_sender.nickname = _message.arguments()[0];
				if (_sender.registered)
					_message_user(":" + old_nick + " NICK " + _sender.nickname + "\r\n", _sender); // send message that user changed nickname.
				else if (!(_sender.username.empty()))
					_register_user();
			}
		}
		
		void _cmd_motd(void)
		{
			_message_user(_generate_reply(RPL_MOTDSTART), _sender);
			_message_user(_generate_reply(RPL_MOTD), _sender);
			_message_user(_generate_reply(RPL_ENDOFMOTD), _sender);
		}

		void _cmd_pong(void)
		{
			_sender.is_ping = false;
			_sender.last_ping = time(NULL);
		}

		void _cmd_privmsg(void)
		{
			std::string destination = _message.arguments().front();
			std::string msg = _sender.get_prefix() + " PRIVMSG " + _message.arguments().front() + " " + _message.arguments().back() + MSG_ENDLINE;

			if (destination.front() == '#')
				_message_channel(msg, _message.arguments().front(), false);
			else
				_message_user(msg, _message.arguments().front());
		}

		void _cmd_join(void)
		{
			_channels[_message.arguments()[0]].add_user(_sender.nickname);
			std::string msg = _sender.get_prefix() + " JOIN " + _message.arguments()[0] + MSG_ENDLINE;
			_message_channel(msg, _message.arguments()[0], true);
		}
	
		void _cmd_unknown(void)
		{
			Debug("User " + _sender.nickname + " sent an Unknown Command: " + _message.command(), DBG_INFO);
			_message_user(":server 421  " + _message.command() + " :Unknown command\r\n", _sender); // 	
		}

};

#endif
