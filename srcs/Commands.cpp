/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:23:01 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 22:48:39 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::map<std::string, Commands::cmd_type> Commands::init_commands(void)
{
	std::map<std::string, Commands::cmd_type> cmd;

	cmd["PASS"] = &Commands::_cmd_pass;
	cmd["NICK"] = &Commands::_cmd_nick;
	cmd["USER"] = &Commands::_cmd_user;
	cmd["OPER"] = &Commands::_cmd_oper;
	cmd["MODE"] = &Commands::_cmd_mode;
	cmd["QUIT"] = &Commands::_cmd_quit;
	cmd["SERVER"] = &Commands::_cmd_server;
	cmd["SQUIT"] = &Commands::_cmd_squit;
	cmd["JOIN"] = &Commands::_cmd_join;
	cmd["PART"] = &Commands::_cmd_part;
	cmd["MODE"] = &Commands::_cmd_mode;
	cmd["TOPIC"] = &Commands::_cmd_topic;
	cmd["NAMES"] = &Commands::_cmd_names;
	cmd["LIST"] = &Commands::_cmd_list;
	cmd["INVITE"] = &Commands::_cmd_invite;
	cmd["KICK"] = &Commands::_cmd_kick;
	cmd["PRIVMSG"] = &Commands::_cmd_privmsg;
	cmd["NOTICE"] = &Commands::_cmd_notice;
	cmd["MOTD"] = &Commands::_cmd_motd;
	cmd["LUSERS"] = &Commands::_cmd_lusers;
	cmd["VERSION"] = &Commands::_cmd_version;
	cmd["STATS"] = &Commands::_cmd_stats;
	cmd["LINKS"] = &Commands::_cmd_links;
	cmd["TIME"] = &Commands::_cmd_time;
	cmd["CONNECT"] = &Commands::_cmd_connect;
	cmd["TRACE"] = &Commands::_cmd_trace;
	cmd["ADMIN"] = &Commands::_cmd_admin;
	cmd["INFO"] = &Commands::_cmd_info;
	cmd["WHO"] = &Commands::_cmd_who;
	cmd["WHOIS"] = &Commands::_cmd_whois;
	cmd["WHOWAS"] = &Commands::_cmd_whowas;
	cmd["KILL"] = &Commands::_cmd_kill;
	cmd["PING"] = &Commands::_cmd_ping;
	cmd["PONG"] = &Commands::_cmd_pong;
	cmd["ERROR"] = &Commands::_cmd_error;
	cmd["AWAY"] = &Commands::_cmd_away;
	return (cmd);
}

std::map<std::string, Commands::cmd_type> Commands::_commands = init_commands();

std::map<int, std::string> Commands::init_replies(void)
{
	std::map<int, std::string> replies;

	replies[RPL_WELCOME] = "Welcome to the Internet Relay Network <nick>!<user>@<host>";
	replies[RPL_YOURHOST] = "Your host is <servername>, running version <ver>";
	replies[RPL_CREATED] = "This server was created <date>";
	replies[RPL_MYINFO] = "<servername> <version> <available_user_modes> <available_channel_modes>";
	replies[RPL_BOUNCE] = "Try server <server name>, port <port number>";
	replies[RPL_USERHOST] = ":*1<reply> *( " " <reply> )";
	replies[RPL_ISON] = ":*1<nick> *( " " <nick> )";
	replies[RPL_AWAY] = "<nick> :<away message>";
	replies[RPL_UNAWAY] = ":You are no longer marked as being away";
	replies[RPL_NOWAWAY] = ":You have been marked as being away";
	replies[RPL_WHOISUSER] = "<nick> <user> <host> * :<real_name>";
	replies[RPL_WHOISSERVER] = "<nick> <server> :<server_info>";
	replies[RPL_WHOISOPERATOR] = "<nick> :is an IRC operator";
	replies[RPL_WHOISIDLE] = "<nick> <secidle> :seconds idle";
	replies[RPL_ENDOFWHOIS] = "<nick> :End of WHOIS list";
	replies[RPL_WHOISCHANNELS] = "<nick> :<channel_list>"; //*( ( "@" / "+" ) <channel> " " )";
	replies[RPL_WHOWASUSER] = "<nick> <user> <host> * :<real_name>";
	replies[RPL_ENDOFWHOWAS] = "<nickname> :End of WHOWAS";
	replies[RPL_LIST] = "<channel> <visible> :<topic>";
	replies[RPL_LISTEND] = ":End of LIST";
	replies[RPL_UNIQOPIS] = "<channel> <nickname>";
	replies[RPL_CHANNELMODEIS] = "<channel> <mode> <mode_params>";
	replies[RPL_NOTOPIC] = "<channel> :No topic is set";
	replies[RPL_TOPIC] = "<channel> :<topic>";
	replies[RPL_INVITING] = "<nick> <channel>";
	replies[RPL_SUMMONING] = "<user> :Summoning user to IRC";
	replies[RPL_INVITELIST] = "<channel> <invitemask>";
	replies[RPL_ENDOFINVITELIST] = "<channel> :End of channel invite list";
	replies[RPL_EXCEPTLIST] = "<channel> <exceptionmask>";
	replies[RPL_ENDOFEXCEPTLIST] = "<channel> :End of channel exception list";
	replies[RPL_VERSION] = "<version>.<debuglevel> <server> :<comments>";
	replies[RPL_WHOREPLY] = "<channel> <user> <host> <server> <nick> <away><servop><chanop> :<hops> <real_name>";
	replies[RPL_ENDOFWHO] = "<name> :End of /WHO list";
	replies[RPL_NAMREPLY] = "= <channel> :<names_list>";
	replies[RPL_ENDOFNAMES] = "<channel> :End of /NAMES list";
	replies[RPL_LINKS] = "<mask> <server> :<hopcount> <server_info>";
	replies[RPL_ENDOFLINKS] = "<mask> :End of LINKS list";
	replies[RPL_BANLIST] = "<channel> <banmask>";
	replies[RPL_ENDOFBANLIST] = "<channel> :End of channel ban list";
	replies[RPL_INFO] = ":<string>";
	replies[RPL_ENDOFINFO] = ":End of INFO list";
	replies[RPL_MOTDSTART] = ":- <server> Message of the day - ";
	replies[RPL_MOTD] = ":- <text>";
	replies[RPL_ENDOFMOTD] = ":End of MOTD command";
	replies[RPL_YOUREOPER] = ":You are now an IRC operator";
	replies[RPL_REHASHING] = "<config file> :Rehashing";
	replies[RPL_YOURESERVICE] = "You are service <servicename>";
	replies[RPL_TIME] = "<server> :<time>";
	replies[RPL_USERSSTART] = ":UserID   Terminal  Host";
	replies[RPL_USERS] = ":<username> <ttyline> <hostname>";
	replies[RPL_ENDOFUSERS] = ":End of users";
	replies[RPL_NOUSERS] = ":Nobody logged in";
	replies[RPL_TRACELINK] = "Link <version & debug level> <destination> <next server> V<protocol version> <link uptime in seconds> <backstream sendq> <upstream sendq>";
	replies[RPL_TRACECONNECTING] = "Try. <class> <server>";
	replies[RPL_TRACEHANDSHAKE] = "H.S. <class> <server>";
	replies[RPL_TRACEUNKNOWN] = "???? <class> [<client IP address in dot form>]";
	replies[RPL_TRACEOPERATOR] = "Oper <class> <nick>";
	replies[RPL_TRACEUSER] = "User <class> <nick>";
	replies[RPL_TRACESERVER] = "Serv <class> <int>S <int>C <server> <nick!user|*!*>@<host|server> V<protocol version>";
	replies[RPL_TRACESERVICE] = "Service <class> <name> <type> <active type>";
	replies[RPL_TRACENEWTYPE] = "<newtype> 0 <client name>";
	replies[RPL_TRACECLASS] = "Class <class> <count>";
	replies[RPL_TRACERECONNECT] = "";
	replies[RPL_TRACELOG] = "File <logfile> <debug level>";
	replies[RPL_TRACEEND] = "<server_name> <version>.<debug_level> :End of TRACE";
	replies[RPL_STATSLINKINFO] = "<linkname> <sendq> <sent messages> <sent Kbytes> <received messages> <received Kbytes> <time open>";
	replies[RPL_STATSCOMMANDS] = "<command> <count>";
	replies[RPL_ENDOFSTATS] = "<stats_letter> :End of STATS report";
	replies[RPL_STATSUPTIME] = ":Server Up <days> days <hours>:<minutes>:<seconds>";
	replies[RPL_STATSOLINE] = "O <hostmask> * <name>";
	replies[RPL_UMODEIS] = "<user mode string>";
	replies[RPL_SERVLIST] = "<name> <server> <mask> <type> <hopcount> <info>";
	replies[RPL_SERVLISTEND] = "<mask> <type> :End of service listing";
	replies[RPL_LUSERCLIENT] = ":There are <intusers> users and <intinvisible> invisible on <intservers> servers";
	replies[RPL_LUSEROP] = "<integer> :operator(s) online";
	replies[RPL_LUSERUNKNOWN] = "<integer> :unknown connection(s)";
	replies[RPL_LUSERCHANNELS] = "<integer> :channels formed";
	replies[RPL_LUSERME] = ":I have <intclients> clients and <intservers> servers";
	replies[RPL_ADMINME] = ":Administrative info about <server>";
	replies[RPL_ADMINLOC1] = ":<info1>";
	replies[RPL_ADMINLOC2] = ":<info2>";
	replies[RPL_ADMINEMAIL] = ":<email>";
	replies[RPL_TRYAGAIN] = "<command> :Please wait a while and try again.";
	replies[ERR_NOSUCHNICK] = "<nickname> :No such nick";
	replies[ERR_NOSUCHSERVER] = "<server name> :No such server";
	replies[ERR_NOSUCHCHANNEL] = "<channel name> :No such channel";
	replies[ERR_CANNOTSENDTOCHAN] = "<channel name> :Cannot send to channel";
	replies[ERR_TOOMANYCHANNELS] = "<channel name> :You have joined too many channels";
	replies[ERR_WASNOSUCHNICK] = "<nick> :There was no such nickname";
	replies[ERR_TOOMANYTARGETS] = "<target> :too many recipients.";
	replies[ERR_NOSUCHSERVICE] = "<service name> :No such service";
	replies[ERR_NOORIGIN] = ":No origin specified";
	replies[ERR_NORECIPIENT] = ":No recipient given (<command>)";
	replies[ERR_NOTEXTTOSEND] = ":No text to send";
	replies[ERR_NOTOPLEVEL] = "<mask> :No toplevel domain specified";
	replies[ERR_WILDTOPLEVEL] = "<mask> :Wildcard in toplevel domain";
	replies[ERR_BADMASK] = "<mask> :Bad Server/host mask";
	replies[ERR_UNKNOWNCOMMAND] = "<command> :Unknown command";
	replies[ERR_NOMOTD] = ":MOTD File is missing";
	replies[ERR_NOADMININFO] = "<server> :No administrative info available";
	replies[ERR_FILEERROR] = ":File error doing <file op> on <file>";
	replies[ERR_NONICKNAMEGIVEN] = ":No nickname given";
	replies[ERR_ERRONEUSNICKNAME] = "<nick> :Erroneous nickname";
	replies[ERR_NICKNAMEINUSE] = "<nick> :Nickname is already in use";
	replies[ERR_NICKCOLLISION] = "<nick> :Nickname collision KILL from <user>@<host>";
	replies[ERR_UNAVAILRESOURCE] = "<nick/channel> :Nick/channel is temporarily unavailable";
	replies[ERR_USERNOTINCHANNEL] = "<nick> <channel> :They aren't on that channel";
	replies[ERR_NOTONCHANNEL] = "<channel> :You're not on that channel";
	replies[ERR_USERONCHANNEL] = "<nick> <channel> :is already on channel";
	replies[ERR_NOLOGIN] = "<user> :User not logged in";
	replies[ERR_SUMMONDISABLED] = ":SUMMON has been disabled";
	replies[ERR_USERSDISABLED] = ":USERS has been disabled";
	replies[ERR_NOTREGISTERED] = "<user> :You have not registered";
	replies[ERR_NEEDMOREPARAMS] = "<command> :Not enough parameters";
	replies[ERR_ALREADYREGISTRED] = ":Unauthorized command (already registered)";
	replies[ERR_NOPERMFORHOST] = ":Your host isn't among the privileged";
	replies[ERR_PASSWDMISMATCH] = ":Password incorrect";
	replies[ERR_YOUREBANNEDCREEP] = ":You are banned from this server";
	replies[ERR_YOUWILLBEBANNED] = "";
	replies[ERR_KEYSET] = "<channel> :Channel key already set";
	replies[ERR_CHANNELISFULL] = "<channel> :Cannot join channel (+l)";
	replies[ERR_UNKNOWNMODE] = "<char> :is unknown mode char to me for <channel>";
	replies[ERR_INVITEONLYCHAN] = "<channel> :Cannot join channel (+i)";
	replies[ERR_BANNEDFROMCHAN] = "<channel> :Cannot join channel (+b)";
	replies[ERR_BADCHANNELKEY] = "<channel> :Cannot join channel (+k)";
	replies[ERR_BADCHANMASK] = "<channel> :Bad Channel Mask";
	replies[ERR_NOCHANMODES] = "<channel> :Channel doesn't support modes";
	replies[ERR_BANLISTFULL] = "<channel> <char> :Channel list is full";
	replies[ERR_NOPRIVILEGES] = ":Permission Denied- You're not an IRC operator";
	replies[ERR_CHANOPRIVSNEEDED] = "<channel> :You're not channel operator";
	replies[ERR_CANTKILLSERVER] = ":You can't kill a server!";
	replies[ERR_RESTRICTED] = ":Your connection is restricted!";
	replies[ERR_UNIQOPPRIVSNEEDED] = ":You're not the original channel operator";
	replies[ERR_NOOPERHOST] = ":No O-lines for your host";
	replies[ERR_UMODEUNKNOWNFLAG] = ":Unknown MODE flag";
	replies[ERR_USERSDONTMATCH] = ":Cannot change mode for other users";	
	replies[ERR_INPUTTOOLONG] = ":Input line was too long";
	replies[PRIVMSG] = ":<nick>!<user>@<host> PRIVMSG <destinatary> :<message>";
	replies[ERR_USERQUIT] = "Quit: <message>";
	replies[ERR_BADPASSWORD] = "Bad Password";
	replies[ERR_PINGTIMEOUT] = "Ping timeout";
	replies[ERR_REGISTERTIMEOUT] = "Registration Timeout";
	replies[ERR_EOFFROMCLIENT] = "EOF from client";
	replies[ERR_KILLED] = "Killed (<server> (<message>))";
	replies[ERR_WHOISTOOMANY] = "Too many results, restrict your query";
	replies[RPL_WHOWASSERVER] = "<nick> <server> :<last_activity>";
	replies[RPL_PONG] = "PONG";
	replies[ERR_SILENT] = "*** silent error ***";
	return (replies);
}

std::map<int, std::string> Commands::_replies = init_replies();


/*
** Constructors, Desctructors, Assignment operators.
*/

Commands::Commands(int message, Client *sender): _sender(sender), _clients(0x0), _channels(0x0), _server(0x0)
{
	_message_user(_generate_reply(message), _sender);
}

Commands::Commands(std::string message, Client *sender, std::map<int, Client> *clients, std::map<std::string, Channel> *channels, Server *server)
: _sender(sender), _clients(clients), _channels(channels), _server(server)
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
Commands::Commands(Commands const &cp) { *this = cp; }
Commands &Commands::operator=(Commands const &cp)
{
	_sender = cp._sender;
	_clients = cp._clients;
	_message = cp._message;
	_channels = cp._channels;
	_server = cp._server;
	return (*this);
}
Commands::~Commands() { }


/*
** command helpers
*/
Client *Commands::_get_client_by_nickname(std::string nick)
{
	for (std::map<int, Client>::iterator it = ++(_clients->begin()); it != _clients->end(); it++ )
		if (it->second.nickname == nick)
			return (&(it->second));
	return (NULL);
}

Channel *Commands::_get_channel_by_name(std::string name)
{
	for (std::map<std::string, Channel>::iterator it = _channels->begin(); it != _channels->end(); it++ )
	{
		if (it->second.get_name() == name)
			return (&(it->second));
	}

	return (NULL);
}

/*
** command parsing and processing
*/

void	Commands::_process()
{
	std::string cmd = _message.command();	
	std::map<std::string, std::string> m;
	
	m["user"] = (_sender->nickname != "") ? _sender->nickname : std::string("*");
	if (!(_sender->registered) && (cmd != "ADMIN" && cmd != "NICK" && cmd != "PASS"
		&& cmd != "PONG" && cmd != "QUIT" && cmd != "USER" && cmd != "VERSION" && cmd != "SERVER"))
		_message_user(_generate_reply(ERR_NOTREGISTERED, m), _sender);
	else
		_run_command(cmd);
}

void Commands::_run_command(std::string &cmd_name)
{
	std::map<std::string, cmd_type>::iterator cmd_it;
	
	Debug("Looking for command", DBG_DEV);
	cmd_it = _commands.find(cmd_name);
	if (cmd_it == _commands.end())
		_cmd_unknown();
	else
	{
		(*this.*(cmd_it->second))();
		_server->commandstats()[cmd_it->first] = ++(_server->commandstats()[cmd_it->first]);
	}
}

/*
** reply generation
*/
std::string Commands::_numeric_reply(int reply)
{
	std::string nb = ft::to_string(reply);

	while (nb.size() < 3)
		nb.insert(nb.begin(), '0');
	return (nb);
}

/*
** user`s send queue must always be cleared
** before sending an error.
*/
std::string Commands::generate_errormsg(int error, std::map<std::string, std::string> v)
{
	std::string message = "";
	if (v.size())
		message += _replace_tags(_replies[error], v);
	else
		message += _replies[error];
	return (message);
}

/*
** generates a reply message replacing a string "mapped" from the numeric reply
** for a string "value". Used when a single value needs to be replaced
*/
std::string Commands::_generate_reply(int reply, std::string mapped, std::string value)
{
	std::string message = ":" + _server->servername() + " " + _numeric_reply(reply) + " " + _sender->nickname + " ";
	std::string reply_msg = _replies[reply];
	std::string str_tofind("<" + mapped + ">");
	size_t find_pos = reply_msg.find(str_tofind);
	if (find_pos != std::string::npos)
		reply_msg.replace(find_pos, str_tofind.size(), value);
	message += reply_msg;
	message += MSG_ENDLINE;
	return (message);
}

/*
** generates a reply message replacing a string "mapped" from the numeric reply
** for a string "value". Used when a multiple values need to be replaced. a Map of
** [mapped] = string must be passed.
*/
std::string Commands::_generate_reply(int reply, std::map<std::string, std::string> v)
{
	std::string message = ":" + _server->servername() + " " + _numeric_reply(reply) + " " + _sender->nickname + " ";
	if (v.size())
		message += _replace_tags(_replies[reply], v);
	else
		message += _replies[reply];
	message += MSG_ENDLINE;
	return (message);
}

std::string Commands::_replace_tags(std::string msg, std::map<std::string, std::string> v)
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

void Commands::_message_all_channels(std::string const &msg, bool sender_too)
{
	std::set<Client *> users;
	for (std::map<std::string, Channel>::iterator it = _channels->begin(); it != _channels->end(); it++)
	{
		if (std::find(it->second.users.begin(), it->second.users.end(), _sender) != it->second.users.end())
			users.insert(it->second.users.begin(), it->second.users.end());
	}
	if (!sender_too)
		users.erase(_sender);
	for (std::set<Client *>::iterator it = users.begin(); it!= users.end(); it++)
		_message_user(msg, *it);
}

/*
** sends a message to a specific channel
*/
void Commands::_message_channel(std::string const &msg, std::string const &channel, bool sender_too)
{
	for (std::vector<Client *>::iterator it = (*_channels)[channel].users.begin(); it != (*_channels)[channel].users.end(); it++)
		if (*it != _sender || sender_too)
			_message_user(msg, *it);
}

/*
** sends a message to a specific user
*/
void Commands::_message_user(std::string msg, std::string const &nickname)
{
	Client *client = _get_client_by_nickname(nickname);

	if (!(client))
		_message_user(_generate_reply(ERR_NOSUCHNICK), _sender);
	else
		_message_user(msg, client);
}

void Commands::_message_user(std::string msg, Client *client)
{
	client->get_send_queue().push_back(msg);
}

/*
** IRC Commands Helpers
*/
void Commands::_register_user(void)
{
	Debug("User Registered", DBG_ERROR);
	std::map<std::string, std::string> v;
	std::string msg;

	if (_sender->password != _server->password())
	{
		_sender->get_send_queue().clear();
		_sender->set_hangup(true, generate_errormsg(ERR_BADPASSWORD));
		return ;
	}
	_sender->registered = true;
	v["nick"] = _sender->nickname;
	v["user"] = _sender->username;
	v["host"] = _sender->hostname;
	v["servername"] = _server->servername();
	v["ver"] = _server->version();
	v["version"] = _server->version();
	v["date"] = _server->formatted_creation_date();
	v["server"] = _server->servername();
	v["intusers"] = ft::to_string(0); //TODO
	v["intinvisible"] = ft::to_string(0); //TODO
	v["intservers"] = ft::to_string(1);
	v["intclients"] = ft::to_string(_clients->size() - 1);
	_message_user(_generate_reply(RPL_WELCOME, v), _sender);
	_message_user(_generate_reply(RPL_YOURHOST, v), _sender);
	_message_user(_generate_reply(RPL_CREATED, v), _sender);
	_message_user(_generate_reply(RPL_MYINFO, v), _sender);
	_message_user(_generate_reply(RPL_LUSERCLIENT, v), _sender);
	_message_user(_generate_reply(RPL_LUSERME, v), _sender);
	_cmd_motd();
	msg = _sender->get_prefix() + " MODE " + _sender->nickname + " " + MODE_USER_DFL;
	Commands(msg, _sender, _clients, _channels, _server);
}

/*
** if the nickname is longer than SRV_MAXNICKLEN, truncate it.
** should only be used after validating the nickname
*/
void Commands::_truncate_nick(std::string &nickname)
{
	if (nickname.size() > SRV_MAXNICKLEN)
		nickname.erase(SRV_MAXNICKLEN);
}

void Commands::_cmd_unknown(void)
{
	Debug("User " + _sender->nickname + " sent an Unknown Command: " + _message.command(), DBG_INFO);
	_message_user(":server 421  " + _message.command() + " :Unknown command\r\n", _sender);
}

/*
** returns wether client1 and client2 share a common channel.
*/
bool Commands::_shared_channel(Client *client1, Client *client2)
{
	if (!client1 || !client2)
		return (false);
	for (channel_iterator it = _channels->begin(); it != _channels->end(); it++)
	{
		if (it->second.is_user(*client1) && it->second.is_user(*client2))
			return (true);
	}
	return (false);
}

/*
** returns wether client1 and client2 share a common channel.
*/
std::string Commands::_channel_list(Client *client)
{
	std::string channel_list;

	if (client)
	{
		for (channel_iterator it = _channels->begin(); it != _channels->end(); it++)
		{
			if (it->second.is_user(*client) && (!(it->second.is_secret()) || it->second.is_user(*_sender)))
			{
				if (it->second.is_operator(*client))
					channel_list += "@";
				else if (it->second.is_voice(*client))
					channel_list += "+";
				channel_list += it->second.get_name() + " ";
			}
		}
	}
	if (channel_list.size() && channel_list[channel_list.size() - 1] == ' ')
		channel_list.erase(channel_list.size() - 1);
	return (channel_list);
}
