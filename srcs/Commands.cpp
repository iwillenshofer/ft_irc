/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:23:01 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/21 15:17:57 by iwillens         ###   ########.fr       */
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
	replies[RPL_WHOISSERVER] = "<nick> <server> :<server info>";
	replies[RPL_WHOISOPERATOR] = "<nick> :is an IRC operator";
	replies[RPL_WHOISIDLE] = "<nick> <integer> :seconds idle";
	replies[RPL_ENDOFWHOIS] = "<nick> :End of WHOIS list";
	replies[RPL_WHOISCHANNELS] = "<nick> :<channel_list>"; //*( ( "@" / "+" ) <channel> " " )";
	replies[RPL_WHOWASUSER] = "<nick> <user> <host> * :<real_name>";
	replies[RPL_ENDOFWHOWAS] = "<nick> :End of WHOWAS";
	replies[RPL_LIST] = "<channel> <# visible> :<topic>";
	replies[RPL_LISTEND] = ":End of LIST";
	replies[RPL_UNIQOPIS] = "<channel> <nickname>";
	replies[RPL_CHANNELMODEIS] = "<channel> <mode> <mode_params>";
	replies[RPL_NOTOPIC] = "<channel> :No topic is set";
	replies[RPL_TOPIC] = "<channel> :<topic>";
	replies[RPL_INVITING] = "<channel> <nick>";
	replies[RPL_SUMMONING] = "<user> :Summoning user to IRC";
	replies[RPL_INVITELIST] = "<channel> <invitemask>";
	replies[RPL_ENDOFINVITELIST] = "<channel> :End of channel invite list";
	replies[RPL_EXCEPTLIST] = "<channel> <exceptionmask>";
	replies[RPL_ENDOFEXCEPTLIST] = "<channel> :End of channel exception list";
	replies[RPL_VERSION] = "<version>.<debuglevel> <server> :<comments>";
	replies[RPL_WHOREPLY] = "<channel> ~<user> <host> <server> <nick> H@ :0 <real_name>";
	replies[RPL_ENDOFWHO] = "<name> :End of /WHO list";
	replies[RPL_NAMREPLY] = "= <channel> :<names_list>";
	replies[RPL_ENDOFNAMES] = "<channel> :End of /NAMES list";
	replies[RPL_LINKS] = "<mask> <server> :<hopcount> <server info>";
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
	replies[RPL_TIME] = "<server> :<string showing server's local time>";
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
	replies[RPL_TRACEEND] = "<server name> <version & debug level> :End of TRACE";
	replies[RPL_STATSLINKINFO] = "<linkname> <sendq> <sent messages> <sent Kbytes> <received messages> <received Kbytes> <time open>";
	replies[RPL_STATSCOMMANDS] = "<command> <count> <byte count> <remote count>";
	replies[RPL_ENDOFSTATS] = "<stats letter> :End of STATS report";
	replies[RPL_STATSUPTIME] = ":Server Up %d days %d:%02d:%02d";
	replies[RPL_STATSOLINE] = "O <hostmask> * <name>";
	replies[RPL_UMODEIS] = "<user mode string>";
	replies[RPL_SERVLIST] = "<name> <server> <mask> <type> <hopcount> <info>";
	replies[RPL_SERVLISTEND] = "<mask> <type> :End of service listing";
	replies[RPL_LUSERCLIENT] = ":There are <intusers> users and <intinvisible> invisible on <intservers> servers";
	replies[RPL_LUSEROP] = "<integer> :operator(s) online";
	replies[RPL_LUSERUNKNOWN] = "<integer> :unknown connection(s)";
	replies[RPL_LUSERCHANNELS] = "<integer> :channels formed";
	replies[RPL_LUSERME] = ":I have <intclients> clients and <intservers> servers";
	replies[RPL_ADMINME] = "<server> :Administrative info";
	replies[RPL_ADMINLOC1] = ":<admin info>";
	replies[RPL_ADMINLOC2] = ":<admin info>";
	replies[RPL_ADMINEMAIL] = ":<admin info>";
	replies[RPL_TRYAGAIN] = "<command> :Please wait a while and try again.";
	replies[ERR_NOSUCHNICK] = "<nickname> :No such nick/channel";
	replies[ERR_NOSUCHSERVER] = "<server name> :No such server";
	replies[ERR_NOSUCHCHANNEL] = "<channel name> :No such channel";
	replies[ERR_CANNOTSENDTOCHAN] = "<channel name> :Cannot send to channel";
	replies[ERR_TOOMANYCHANNELS] = "<channel name> :You have joined too many channels";
	replies[ERR_WASNOSUCHNICK] = "<nickname> :There was no such nickname";
	replies[ERR_TOOMANYTARGETS] = "<target> :<error code> recipients. <abort message>";
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
	replies[ERR_USERONCHANNEL] = "<user> <channel> :is already on channel";
	replies[ERR_NOLOGIN] = "<user> :User not logged in";
	replies[ERR_SUMMONDISABLED] = ":SUMMON has been disabled";
	replies[ERR_USERSDISABLED] = ":USERS has been disabled";
	replies[ERR_NOTREGISTERED] = ":You have not registered";
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

	replies[329] = "<channel> <creation>"; // creation time
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
Commands::Commands(Commands const &cp): _sender(cp._sender), _clients(cp._clients), _channels(cp._channels) { *this = cp; }
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
	for (std::map<int, Client>::iterator it = _clients->begin(); it != _clients->end(); it++ )
		if (it->second.nickname == nick)
			return (&(it->second));
	return (NULL);
}

/*
** command parsing and processing
*/

void	Commands::_process()
{
	_run_command(_message.command());
}

void Commands::_run_command(std::string &cmd_name)
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
std::string Commands::_numeric_reply(int reply)
{
	std::string nb = ft::to_string(reply);

	while (nb.size() < 3)
		nb.insert(nb.begin(), '0');
	return (nb);
}

std::string Commands::_generate_reply(int reply, std::map<std::string, std::string> v)
{
	std::string message = ":localhost " + _numeric_reply(reply) + " " + _sender->nickname + " ";
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
void Commands::_message_channel(std::string const &msg, std::string const &channel, bool sender_too)
{
	for (std::vector<std::string>::iterator it = (*_channels)[channel].users.begin(); it != (*_channels)[channel].users.end(); it++)
		if (*it != _sender->nickname || sender_too)
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

	_sender->registered = true;
	_message_user(_generate_reply(RPL_WELCOME, v), _sender);
	_message_user(_generate_reply(RPL_YOURHOST, v), _sender);
	_message_user(_generate_reply(RPL_CREATED, v), _sender);
	_message_user(_generate_reply(RPL_MYINFO, v), _sender);
	_message_user(_generate_reply(RPL_LUSERCLIENT, v), _sender);
	_message_user(_generate_reply(RPL_LUSERME, v), _sender);

	_cmd_motd();
	
	std::string msg = _sender->get_prefix() + " MODE " + _sender->nickname + " :+iw" + MSG_ENDLINE;
	_message_user(msg, _sender);

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

bool Commands::_validate_nick(std::string const &nickname) const
{
	std::string special("[]\\`_^{|}");

	if (!nickname.size())
		return (false);
	if (special.find(nickname[0]) == std::string::npos && !(std::isalpha(nickname[0])))
		return (false);
	for (std::string::const_iterator it = nickname.begin(); it != nickname.end(); it++)
	{
		if (!(std::isalnum(*it)) && special.find(*it) == std::string::npos && *it != '-')
			return (false);
	}
	return (true);
}

void Commands::_cmd_unknown(void)
{
	Debug("User " + _sender->nickname + " sent an Unknown Command: " + _message.command(), DBG_INFO);
	_message_user(":server 421  " + _message.command() + " :Unknown command\r\n", _sender);
}
