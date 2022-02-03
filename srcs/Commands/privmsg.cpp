/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:03 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/02 21:04:29 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.3 Sending messages
**	
**	3.3.1 Private messages
**	Command: PRIVMSG
**	Parameters: <msgtarget> <text to be sent>
**	
**	PRIVMSG is used to send private messages between users, as well as to
**	send messages to channels.  <msgtarget> is usually the nickname of
**	the recipient of the message, or a channel name.
**	
**	The <msgtarget> parameter may also be a host mask (#<mask>) or server
**	mask ($<mask>).  In both cases the server will only send the PRIVMSG
**	to those who have a server or host matching the mask.  The mask MUST
**	have at least 1 (one) "." in it and no wildcards following the last
**	".".  This requirement exists to prevent people sending messages to
**	"#*" or "$*", which would broadcast to all users.  Wildcards are the
**	'*' and '?'  characters.  This extension to the PRIVMSG command is
**	only available to operators.
**	
**	Numeric Replies:
**			ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
**			ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
**			ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
**			ERR_NOSUCHNICK
**			RPL_AWAY
**	
**	Examples:
**	:Angel!wings@irc.org PRIVMSG Wiz :Are you receiving this message ?
**									; Message from Angel to Wiz.
**	
**	PRIVMSG Angel :yes I'm receiving it !
**									; Command to send a message to Angel.
**	
**	PRIVMSG jto@tolsun.oulu.fi :Hello !
**									; Command to send a message to a user
**									on server tolsun.oulu.fi with
**									username of "jto".
**	
**	PRIVMSG kalt%millennium.stealth.net@irc.stealth.net :Are you a frog?
**									; Message to a user on server
**									irc.stealth.net with username of
**									"kalt", and connected from the host
**									millennium.stealth.net.
**	
**	PRIVMSG kalt%millennium.stealth.net :Do you like cheese?
**									; Message to a user on the local
**									server with username of "kalt", and
**									connected from the host
**									millennium.stealth.net.
**	
**	PRIVMSG Wiz!jto@tolsun.oulu.fi :Hello !
**									; Message to the user with nickname
**									Wiz who is connected from the host
**									tolsun.oulu.fi and has the username
**									"jto".
**	
**	PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting.
**									; Message to everyone on a server
**									which has a name matching *.fi.
**	
**	PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions
**									; Message to all users who come from
**									a host which has a name matching
**									*.edu.
*/


std::pair<std::string, std::string> __split_str(std::string const &key, char c)
{
	size_t pos;
	std::string first;
	std::string second;

	pos = key.find(c);
	if (pos != std::string::npos)
	{
		first = key.substr(0, pos);
		second = key.substr(pos + 1);
	}
	else
		first = key;
	return (std::make_pair(first, second));
}

std::map<std::string, std::string> __split_nick(std::string const &key)
{

	std::map<std::string, std::string> m;
	std::pair<std::string, std::string> v;

	m["nick"] = "";
	m["user"] = "*";
	m["host"] = "*";
	m["server"] = "";
	v = __split_str(key, '@');
	m["server"] = v.second;
	v = __split_str(v.first, '%');
	m["host"] = v.second;
	v = __split_str(v.first, '!');
	m["user"] = v.second;
	m["nick"] = v.first;
	return (m);
}

void	Commands::__priv_msg_reply(int msg, std::map<std::string, std::string> *m)
{
	if (_message.command() != "NOTICE")
		_message_user(_generate_reply(msg), _sender);
	(void)m;
}

void	Commands::__priv_msg_send(std::string target)
{
	if (Message::is_bnf_channel(target))
	{
		std::string msg = _sender->get_prefix() + " " + _message.command() + " " + target + " " + _message.arguments(_message.arguments().size() - 1) + MSG_ENDLINE;
		_message_channel(msg, _message.arguments(0), false);
	}
	else if (Message::is_bnf_nickname(target))
		__priv_msg_send(*(_get_client_by_nickname(target)));
}

void	Commands::__priv_msg_send(Client &client)
{
	std::map<std::string, std::string> m;
	std::string msg = _sender->get_prefix() + " " + _message.command() + " " + client.nickname + " " + _message.arguments(_message.arguments().size() - 1) + MSG_ENDLINE;

	_message_user(msg, _message.arguments(0));
	if (client.is_away())
	{
		m["nick"] = client.nickname;
		m["away message"] = client.away_message;
		__priv_msg_reply(RPL_AWAY, &m);
	}
}

void	Commands::__priv_msg_process_mask(std::string &target)
{
	char masktype;
	std::vector<Client> targets;
	std::map<std::string, std::string> m;
	int is_targetmask = Message::is_bnf_targetmask(target);

	m["channel name"] = target;
	Debug("PRIVMSG Process Mask", DBG_DEV);
	if (is_targetmask == BNF_TARGETMSK_NOTOPLEVEL)
		__priv_msg_reply(ERR_NOTOPLEVEL);
	else if (is_targetmask && is_targetmask == BNF_TARGETMSK_WILDTOPLEVEL)
		__priv_msg_reply(ERR_WILDTOPLEVEL);
	else
	{
		Debug("AREWEHERE:");
		masktype = target[0];
		target.erase(0, 1);
		for (client_iterator it = ++(_clients->begin()); it != _clients->end(); it++)
		{
			if ((masktype == '#' && Mask::match_raw(target, it->second.hostname))
			|| (masktype == '$' && Mask::match_raw(target, _server->servername())))
				targets.push_back(it->second);
		}
		if (targets.size() > SRV_MAXTARGETS && !(_sender->is_operator()))
			__priv_msg_reply(ERR_TOOMANYTARGETS);
		else if (!(targets.size()))
			__priv_msg_reply(ERR_NOSUCHCHANNEL);
		else
		{
			for (std::vector<Client>::iterator it = targets.begin(); it != targets.end(); it++)
				__priv_msg_send(it->nickname);
		}
	}
}

void	Commands::__priv_msg_process_channel(std::string &target)
{
	Channel *channel;
	std::map<std::string, std::string> m;

	Debug("PRIVMSG Process Channel", DBG_DEV);
	m["channel name"] = target;
	channel = _get_channel_by_name(target);
	if (!(channel))
		__priv_msg_reply(ERR_NOSUCHCHANNEL, &m);
	else if (channel->is_banned(*_sender) || (!(channel->is_user(_sender->nickname)) && (channel->is_moderated() || channel->is_no_outside())))
		__priv_msg_reply(ERR_CANNOTSENDTOCHAN, &m);
	else
		__priv_msg_send(target);
}

void	Commands::__priv_msg_process_nick(std::string &target)
{
	Client *client;
	std::map<std::string, std::string> m;
	std::map<std::string, std::string> targetmap = __split_nick(target);
	
	m["nickname"] = target;
	m["nick"] = target;
	Debug("PRIVMSG Process Nick", DBG_DEV);
	if (!(Message::is_bnf_nickname(targetmap["nick"])) || (targetmap["server"] != "" && targetmap["server"] != _server->servername()))
		__priv_msg_reply(ERR_NOSUCHNICK, &m);
	else
	{
		client = NULL;
		for (client_iterator it = ++(_clients->begin()); it != _clients->end(); it++)
		{
			if (Mask::match(it->second, targetmap["nick"] + "!" + targetmap["user"] + "@" + targetmap["host"]))
			{
				client = &(it->second);
				break ;
			}
		}
		if (!client)
			__priv_msg_reply(ERR_NOSUCHNICK, &m);
		else
			__priv_msg_send(*client);
	}
}

void	Commands::_cmd_privmsg(void)
{
	int is_targetmask;
	std::string target;
	std::map<std::string, std::string> m;
	
	Debug("PRIVMSG", DBG_DEV);
	m["command"] = _message.command();
	if (!(_message.arguments().size()))
		__priv_msg_reply(ERR_NORECIPIENT, &m);
	else if (_message.arguments().size() == 1)
		__priv_msg_reply(ERR_NOTEXTTOSEND);
	else
	{
		target = _message.arguments(0);
		m["nickname"] = target;
		is_targetmask = Message::is_bnf_targetmask(target);
		Debug("TARGETMASK:" + ft::to_string(is_targetmask));
		if (is_targetmask)
			__priv_msg_process_mask(target);
		else if (Message::is_bnf_channel(target))
			__priv_msg_process_channel(target);
		else if (!(Message::is_bnf_msgto(target)))
			__priv_msg_reply(ERR_NOSUCHNICK, &m);
		else
			__priv_msg_process_nick(target);
	}
}
