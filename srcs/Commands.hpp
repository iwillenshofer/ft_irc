/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:07:16 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/17 23:44:14 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP


# include <map>
# include <set>
# include <vector>
# include <string>
# include <algorithm>
# include <exception>
# include "Debug.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "utilities.hpp"
# include "server_defaults.hpp"

//class Client;

class Message
{
	public:
		Message(void) {};
		Message(std::string message): _message(message)
		{
			_disassemble();
			_validate();
		}
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
		** disassembles _message into _prefix, _command and [_arguments]
		*/
		void _disassemble(void)
		{
			std::string user_message;
			std::string msg = _message;

			_message = ft::trim(_message);
			if (!msg.size())
				return;
			if (msg[0] == ':')
			{
				_prefix = msg.substr(0, msg.find(' '));
				msg.erase(0, _prefix.size());
				_prefix.erase(_prefix.begin());
				msg = ft::trim(msg);
			}
			if (msg.find(" :") != msg.npos)
			{
				user_message = ft::trim(msg.substr(msg.find(" :"), msg.size()));
				msg.erase(msg.size() - user_message.size());
				user_message.erase(0, 1);
			}
			msg = ft::trim(msg);
			_arguments = ft::split(msg, ' ');
			if (_arguments.size())
			{
				_command = _arguments[0];
				_arguments.erase(_arguments.begin());
			}
			_arguments.push_back(user_message);
		}

		void _validate(void)
		{
			if (_message.size() > MSG_MAXMSGSIZE)
				throw InputLineTooLong();
			if (!(_message.size()) || !(_command.size()))
				throw EmptyMessage();
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

		struct InputLineTooLong : public std::exception
		{
				virtual const char*	what() const throw() { return ("417: Input line was too long."); }
		};

		struct EmptyMessage : public std::exception
		{
				virtual const char*	what() const throw() { return ("Empty Message."); }
		};
};

/*
** the command Class parses the command, creates a response,
** and adds it to the appropriate clients send queue.
*/

class Commands
{
	public:
		Commands(int message, Client *sender): _sender(sender), _clients(0x0), _channels(0x0)
		{
			_message_user(_generate_reply(message), _sender);
		}

		Commands(std::string message, Client *sender, std::map<int, Client> *clients, std::map<std::string, Channel> *channels): _sender(sender), _clients(clients), _channels(channels)
		{ 
			try
			{
				_message = Message(message);
			}
			catch (const Message::EmptyMessage &e)
			{
				return;
			}
			catch (const Message::InputLineTooLong &e)
			{
				_message_user(_generate_reply(ERR_INPUTTOOLONG), _sender);
				return ;
			}
			_process();
		}
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
		Client							*_sender;
		std::map<int, Client>			*_clients;
		std::map<std::string, Channel>	*_channels;


		typedef  void (Commands::*cmd_type)(void);
		static std::map<std::string, cmd_type> init_commands(void);
		static std::map<std::string, cmd_type> _commands;
		static std::map<int, std::string> init_replies(void);
		static std::map<int, std::string> _replies;
		
		/*
		** IRC Commands
		** Connection Registration
		** RFC 2821 Section 3.1
		*/
		void _cmd_pass(void);
		void _cmd_nick(void);
		void _cmd_user(void);
		void _cmd_mode(void);
		void _cmd_oper(void);
		void _cmd_quit(void);

		/*
		** Channel Operations
		** RFC 2821 Section 3.2
		*/
		void _cmd_join(void);
		void _cmd_part(void);
		void _cmd_mode_channel(void);
		void _cmd_topic(void);
		void _cmd_names(void);
		void _cmd_list(void);
		void _cmd_invite(void);
		void _cmd_kick(void);

		/*
		** Channel Operations
		** RFC 2821 Section 3.3
		*/
		void _cmd_privmsg(void);
		void _cmd_notice(void);

		/*
		** Server Queries and Commands
		** RFC 2821 Section 3.4
		*/
		void _cmd_motd(void);
		void _cmd_lusers(void);
		void _cmd_version(void);
		void _cmd_stats(void);
		void _cmd_links(void);
		void _cmd_time(void);
		void _cmd_trace(void);
		void _cmd_admin(void);
		void _cmd_info(void);

		/*
		** User based queries
		** RFC 2821 Section 3.6
		*/
		void _cmd_who(void);
		void _cmd_whois(void);
		void _cmd_whowas(void);

		/*
		** Miscellaneous messages
		** RFC 2821 Section 3.7
		*/
		void _cmd_kill(void);
		void _cmd_ping(void);
		void _cmd_pong(void);
		void _cmd_error(void);
		
		
		/*
		** command helpers
		*/
		Client *_get_client_by_nickname(std::string nick)
		{
			for (std::map<int, Client>::iterator it = _clients->begin(); it != _clients->end(); it++ )
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
			std::string nb = ft::to_string(reply);

			while (nb.size() < 3)
				nb.insert(nb.begin(), '0');
			return (nb);
		}

		std::string _generate_reply(int reply, std::map<std::string, std::string> v = std::map<std::string, std::string>())
		{
			std::string message = ":localhost " + _numeric_reply(reply) + " " + _sender->nickname + " ";
			if (v.size())
				message += _replace_tags(_replies[reply], v);
			else
				message += _replies[reply];
			message += MSG_ENDLINE;
			return (message);
		}

		std::string _replace_tags(std::string msg, std::map<std::string, std::string> v)
		{

			size_t find_pos;
			
			for (std::map<std::string, std::string>::iterator it = v.begin(); it != v.end(); it++)
			{
				std::string str_tofind("<" + it->first + ">");
				find_pos = msg.find(str_tofind);
				if (find_pos != std::string::npos)
					msg.replace(find_pos, str_tofind.size(), it->second);
			}
			return (msg);
		}


		/*
		** sends a message to everyone that is in a channel the _sender is.
		*/

		void _message_all_channels(std::string const &msg, bool sender_too)
		{
			std::set<std::string> users;
			for (std::map<std::string, Channel>::iterator it = _channels->begin(); it != _channels->end(); it++)
			{
				if (std::find(it->second.users.begin(), it->second.users.end(), _sender->nickname) != it->second.users.end())
					users.insert(it->second.users.begin(), it->second.users.end());
			}
			if (!sender_too)
				users.erase(_sender->nickname);
			for (std::set<std::string>::iterator it = users.begin(); it!= users.end(); it++)
				_message_user(msg, *it);
		}

		/*
		** sends a message to a specific channel
		*/
		void _message_channel(std::string const &msg, std::string const &channel, bool sender_too)
		{
			for (std::vector<std::string>::iterator it = (*_channels)[channel].users.begin(); it != (*_channels)[channel].users.end(); it++)
				if (*it != _sender->nickname || sender_too)
					_message_user(msg, *it);
		}

		/*
		** sends a message to a specific user
		*/
		void _message_user(std::string msg, std::string const &nickname)
		{
			Client *client = _get_client_by_nickname(nickname);

			if (!(client))
				_message_user(_generate_reply(ERR_NOSUCHNICK), _sender);
			else
				_message_user(msg, client);
		}

		void _message_user(std::string msg, Client *client)
		{
			client->get_send_queue().push_back(msg);
		}

		/*
		** IRC Commands Helpers
		*/
		void _register_user(void)
		{
			Debug("User Registered", DBG_ERROR);
			_sender->registered = true;
			_message_user(_generate_reply(RPL_WELCOME), _sender);
			_message_user(_generate_reply(RPL_YOURHOST), _sender);
			_message_user(_generate_reply(RPL_CREATED), _sender);
			_message_user(_generate_reply(RPL_MYINFO), _sender);
			_cmd_motd();
			std::string msg = _sender->get_prefix() + " MODE " + _sender->nickname + " :+iw" + MSG_ENDLINE;
			_message_user(msg, _sender);

		}
		
		bool _validate_nick(std::string const &nickname) const
		{
			(void)nickname;			
			return (true);
		}

		void _cmd_unknown(void)
		{
			Debug("User " + _sender->nickname + " sent an Unknown Command: " + _message.command(), DBG_INFO);
			_message_user(":server 421  " + _message.command() + " :Unknown command\r\n", _sender);
		}

		/*
		** Commands not Implemented:
		** 3.1.6 Service
		** 3.1.8 Squit
		** 3.4.7 Connect
		** 3.5.1 Servlist
		** 3.5.2 Squery
		**
		** Optional Commands
		** 4.1 Away
		** 4.2 Rehash
		** 4.3 Die
		** 4.4 Restart
		** 4.5 Summon
		** 4.6 Users
		** 4.7 Operwall
		** 4.8 Userhost
		** 4.9 Ison
		*/
};

#endif
