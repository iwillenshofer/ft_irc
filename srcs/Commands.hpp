/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:07:16 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/28 22:49:36 by iwillens         ###   ########.fr       */
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
# include "Mask.hpp"
# include "Debug.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Server.hpp"
# include "Message.hpp"
# include "utilities.hpp"
# include "server_defaults.hpp"

class Channel;
class Client;
class Server;
/*
** the command Class parses the command, creates a response,
** and adds it to the appropriate clients send queue.
*/

class Commands
{
	public:
		typedef std::map<std::string, Channel>::iterator	channel_iterator;
		typedef std::map<int, Client>::iterator			client_iterator;


		Commands(int message, Client *sender);
		Commands(std::string message, Client *sender, std::map<int, Client> *clients, std::map<std::string, Channel> *channels, Server *server);
		Commands(Commands const &cp);
		Commands &operator=(Commands const &cp);
		virtual ~Commands();
		static std::string generate_errormsg(int error, std::map<std::string, std::string> v = std::map<std::string, std::string>());
	
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
		void _cmd_mode_user(void);
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
		Channel *_get_channel_by_name(std::string name);

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
		static std::string _replace_tags(std::string msg, std::map<std::string, std::string> v);

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
		** Single command helpers
		*/
		void __perform_whois(std::vector<std::string> &v);
		void __perform_who(Client &client, std::map<std::string, std::string> &arguments, Channel *channel = NULL);
		std::vector<std::string> __perform_names(Channel &channel, bool add_invisible = true, bool end_names = true);

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


/*
**
	  4.1 Connection Registration .................................   
         4.1.1 Password message ...................................   OK
         4.1.2 Nickname message ...................................   OK
         4.1.3 User message .......................................   OK
         4.1.4 Server message .....................................   
         4.1.5 Operator message ...................................   
         4.1.6 Quit message .......................................   OK
         4.1.7 Server Quit message ................................   
      4.2 Channel operations ......................................   
         4.2.1 Join message .......................................   OK
         4.2.2 Part message .......................................   OK
         4.2.3 Mode message .......................................   OK
            4.2.3.1 Channel modes .................................   OK
            4.2.3.2 User modes ....................................   OK
         4.2.4 Topic message ......................................   
         4.2.5 Names message ......................................   OK
         4.2.6 List message .......................................   
         4.2.7 Invite message .....................................   OK
         4.2.8 Kick message .......................................   
      4.3 Server queries and commands .............................   
         4.3.1 Version message ....................................   
         4.3.2 Stats message ......................................   
         4.3.3 Links message ......................................   
         4.3.4 Time message .......................................   
         4.3.5 Connect message ....................................   
         4.3.6 Trace message ......................................   
         4.3.7 Admin message ......................................   OK
         4.3.8 Info message .......................................   
      4.4 Sending messages ........................................   
         4.4.1 Private messages ...................................   
         4.4.2 Notice messages ....................................   
      4.5 User-based queries ......................................   
         4.5.1 Who query ..........................................   OK
         4.5.2 Whois query ........................................   OK
         4.5.3 Whowas message .....................................   OK
      4.6 Miscellaneous messages ..................................   
         4.6.1 Kill message .......................................   
         4.6.2 Ping message .......................................   OK
         4.6.3 Pong message .......................................   OK
         4.6.4 Error message ......................................   OK




**
*/













};

#endif
