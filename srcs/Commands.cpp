/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:23:01 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/14 23:10:18 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::map<std::string, Commands::cmd_type> Commands::init_commands(void)
{
	std::map<std::string, Commands::cmd_type> cmd;

	cmd["NICK"] = &Commands::_cmd_nick;
	cmd["USER"] = &Commands::_cmd_user;
	cmd["MOTD"] = &Commands::_cmd_motd;
	cmd["PONG"] = &Commands::_cmd_pong;
	cmd["PRIVMSG"] = &Commands::_cmd_privmsg;

	return (cmd);
}

std::map<std::string, Commands::cmd_type> Commands::_commands = init_commands();

std::map<int, std::string> Commands::init_replies(void)
{
	std::map<int, std::string> replies;

	replies[RPL_WELCOME] = "Welcome to the Internet Relay Network <nick>!<user>@<host>";
	replies[RPL_YOURHOST] = "Your host is <servername>, running version <ver>";
	replies[RPL_CREATED] = "This server was created <date>";
	replies[RPL_MYINFO] = "<servername> <version> <available user modes> <available channel modes>";
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
//	replies[RPL_WHOISCHANNELS] = "<nick> :*( ( "@" / "+" ) <channel> " " )";
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
//	replies[RPL_WHOREPLY] = "<channel> <user> <host> <server> <nick>( "H" / "G" > ["*"] [ ( "@" / "+" ) ]:<hopcount> <real_name>";
	replies[RPL_ENDOFWHO] = "<name> :End of WHO list";
//	replies[RPL_NAMREPLY] = "( "=" / "*" / "@" ) <channel>:[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )";
	replies[RPL_ENDOFNAMES] = "<channel> :End of NAMES list";
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
	replies[RPL_LUSERCLIENT] = ":There are <integer> users and <integer> services on <integer> servers";
	replies[RPL_LUSEROP] = "<integer> :operator(s) online";
	replies[RPL_LUSERUNKNOWN] = "<integer> :unknown connection(s)";
	replies[RPL_LUSERCHANNELS] = "<integer> :channels formed";
	replies[RPL_LUSERME] = ":I have <integer> clients and <integer> servers";
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
	replies[PRIVMSG] = ":<nick>!<user>@<host> PRIVMSG <destinatary> :<message>";
	return (replies);
}

std::map<int, std::string> Commands::_replies = init_replies();
