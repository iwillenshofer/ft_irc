/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:07:16 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 17:16:59 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP


# include <map>
# include <set>
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
			std::string nb = ft::to_string(reply);

			while (nb.size() < 3)
				nb.insert(nb.begin(), '0');
			return (nb);
		}

		std::string _generate_reply(int reply, std::map<std::string, std::string> v = std::map<std::string, std::string>())
		{
			std::string message = ":localhost " + _numeric_reply(reply) + " " + _sender.nickname + " ";
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
			for (std::map<std::string, Channel>::iterator it = _channels.begin(); it !=_channels.end(); it++)
			{
				if (std::find(it->second.users.begin(), it->second.users.end(), _sender.nickname) != it->second.users.end())
					users.insert(it->second.users.begin(), it->second.users.end());
			}
			if (!sender_too)
				users.erase(_sender.nickname);
			for (std::set<std::string>::iterator it = users.begin(); it!= users.end(); it++)
				_message_user(msg, *it);
		}

		/*
		** sends a message to a specific channel
		*/
		void _message_channel(std::string const &msg, std::string const &channel, bool sender_too)
		{
			for (std::vector<std::string>::iterator it = _channels[channel].users.begin(); it !=_channels[channel].users.end(); it++)
				if (*it != _sender.nickname || sender_too)
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
			std::string msg = _sender.get_prefix() + " MODE " + _sender.nickname + " :+iw" + MSG_ENDLINE;
			_message_user(msg, _sender);

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
				_sender.realname = ft::trim(_message.arguments()[3]);
				if (_sender.realname.size() && _sender.realname[0] == ':')
					_sender.realname.erase(_sender.realname.begin());
				_sender.username = ft::trim(_message.arguments()[0]);
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

			if (destination.at(0) == '#')
				_message_channel(msg, _message.arguments().front(), false);
			else
				_message_user(msg, _message.arguments().front());
		}

		void _cmd_join(void)
		{
			if (std::find(_channels[_message.arguments()[0]].users.begin(), _channels[_message.arguments()[0]].users.end(), _sender.nickname) != _channels[_message.arguments()[0]].users.end())
				return ; // user is already in channel.
			_channels[_message.arguments()[0]].add_user(_sender.nickname);
			std::string msg = _sender.get_prefix() + " JOIN " + _message.arguments()[0] + MSG_ENDLINE;
			_message_channel(msg, _message.arguments()[0], true);
		}

		void _cmd_part(void)
		{
			std::string msg = _sender.get_prefix() + " PART " + _message.arguments()[0] + MSG_ENDLINE;
			_message_channel(msg, _message.arguments()[0], true);
			_channels[_message.arguments()[0]].remove_user(_sender.nickname);
		}
	
		void _cmd_quit(void)
		{
			std::string msg = _sender.get_prefix() + " QUIT " + _message.arguments().back() + MSG_ENDLINE;
			_message_all_channels(msg, false);
			for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
				it->second.remove_user(_sender.nickname);
			_sender.set_hangup(true);
		}

		void _cmd_mode(void)
		{
//			":ircu2.example.irc.com 353 iwillens2 = #brasil :@iwillens2"
//			353 iwillens2 #brasil :iwillens2
			_message.print();
			std::string users;
			std::map<std::string, std::string> arguments;
	
			for (std::vector<std::string>::iterator it = _channels[_message.arguments()[0]].users.begin(); it != _channels[_message.arguments()[0]].users.end(); it++ )
				users += "@" + *it + ' ';
			if (users.size())
				users.erase(users.length() - 1);
			arguments["channel"] = _message.arguments()[0];
			arguments["name"] = _message.arguments()[0];
			arguments["names_list"] = users;
			arguments["mode"] = "+";
			arguments["mode_params"] = "";
			arguments["creation"] = "1642347646";
			_message_user(_generate_reply(RPL_NAMREPLY, arguments), _sender);
			_message_user(_generate_reply(RPL_ENDOFNAMES, arguments), _sender);
			_message_user(_generate_reply(RPL_CHANNELMODEIS, arguments), _sender);
			_message_user(_generate_reply(329, arguments), _sender);
		}

		void _cmd_who(void)
		{
			std::map<std::string, std::string> arguments;
			Client *client;
			arguments["channel"] = _message.arguments()[0];
			arguments["name"] = _message.arguments()[0];
			arguments["server"] = "*.localhost";

			for (std::vector<std::string>::iterator it = _channels[_message.arguments()[0]].users.begin(); it != _channels[_message.arguments()[0]].users.end(); it++ )
			{
				client = _get_client_by_nickname(*it);
				arguments["user"] = client->username;
				arguments["host"] = client->hostname.size() ? client->hostname : "hostname";
				arguments["nick"] = client->nickname;
				arguments["real_name"] = client->realname;
				_message_user(_generate_reply(RPL_WHOREPLY, arguments), _sender);
			}
			_message_user(_generate_reply(RPL_ENDOFWHO, arguments), _sender);
		}

		void _cmd_unknown(void)
		{
			Debug("User " + _sender.nickname + " sent an Unknown Command: " + _message.command(), DBG_INFO);
			_message_user(":server 421  " + _message.command() + " :Unknown command\r\n", _sender); // 	
		}

};

#endif
