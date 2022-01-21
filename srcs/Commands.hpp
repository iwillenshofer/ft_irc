/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:07:16 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/21 15:55:47 by iwillens         ###   ########.fr       */
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
# include <cctype>
# include "Debug.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Server.hpp"
# include "Message.hpp"
# include "utilities.hpp"
# include "server_defaults.hpp"

class Client;

/*
** the command Class parses the command, creates a response,
** and adds it to the appropriate clients send queue.
*/

class Commands
{
	public:
		Commands(int message, Client *sender);
		Commands(std::string message, Client *sender, std::map<int, Client> *clients, std::map<std::string, Channel> *channels, Server *server);
		Commands(Commands const &cp);
		Commands &operator=(Commands const &cp);
		virtual ~Commands();
	
	private:
		Commands(void);
		Message							_message; // parsed command
		Client							*_sender;
		std::map<int, Client>			*_clients;
		std::map<std::string, Channel>	*_channels;
		Server							*_server;

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
		Client *_get_client_by_nickname(std::string nick);

		/*
		** command parsing and processing
		*/
		void	_process();
		void _run_command(std::string &cmd_name);

		/*
		** reply generation
		*/
		std::string _numeric_reply(int reply);
		std::string _generate_reply(int reply, std::map<std::string, std::string> v = std::map<std::string, std::string>());
		std::string _replace_tags(std::string msg, std::map<std::string, std::string> v);

		/*
		** sends a message to everyone that is in a channel the _sender is.
		*/

		void _message_all_channels(std::string const &msg, bool sender_too);

		/*
		** sends a message to a specific channel
		*/
		void _message_channel(std::string const &msg, std::string const &channel, bool sender_too);

		/*
		** sends a message to a specific user
		*/
		void _message_user(std::string msg, std::string const &nickname);
		void _message_user(std::string msg, Client *client);

		/*
		** IRC Commands Helpers
		*/
		void _register_user(void);	
		void _truncate_nick(std::string &nickname);
		bool _validate_nick(std::string const &nickname) const;
		void _cmd_unknown(void);

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
