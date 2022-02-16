/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:16 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 22:23:04 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.2.5 Names message
**	Command: NAMES
**	Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
**	
**	By using the NAMES command, a user can list all nicknames that are
**	visible to him. For more details on what is visible and what is not,
**	see "Internet Relay Chat: Channel Management" [IRC-CHAN].  The
**	<channel> parameter specifies which channel(s) to return information
**	about.  There is no error reply for bad channel names.
**	
**	If no <channel> parameter is given, a list of all channels and their
**	occupants is returned.  At the end of this list, a list of users who
**	are visible but either not on any channel or not on a visible channel
**	are listed as being on `channel' "*".
**	
**	If the <target> parameter is specified, the request is forwarded to
**	that server which will generate the reply.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numerics:
**			ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
**			RPL_NAMREPLY                    RPL_ENDOFNAMES
**	
**	
**	Examples:
**	NAMES #twilight_zone,#42        ; Command to list visible users on
**									#twilight_zone and #42
**	
**	NAMES                           ; Command to list all visible
**									channels and users
**
** [IMPLEMENTATION NOTES]
** Since ERR_TOOMANYMATCHES is not defined in RFC, it was not implemented.
*/

std::vector<Client *> Commands::__perform_names(Channel &channel, bool add_invisible, bool end_names)
{
	std::map<std::string, std::string> m;
	std::vector<Client *> users = channel.users;
	std::vector<Client *> shown_users;
	std::string prefix; 

	for (std::vector<Client *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if (!(add_invisible) && (*it)->is_invisible())
			continue ;
		shown_users.push_back(*it);
	}
	for (std::vector<Client *>::iterator it = users.begin(); it != users.end(); it++)
	{
		prefix = "";
		if (channel.is_operator(**it))
			prefix = "@";
		else if (channel.is_voice(**it))
			prefix = "+";
		m["names_list"] += prefix + (*it)->nickname + ' ';	
	}
	if (m["names_list"].size() && m["names_list"][m["names_list"].size() - 1] == ' ')
		m["names_list"].erase(m["names_list"].size() - 1);
	m["channel"] = channel.get_name();
	_message_user(_generate_reply(RPL_NAMREPLY, m), _sender);
	if (end_names)
		_message_user(_generate_reply(RPL_ENDOFNAMES, m), _sender);
	return (shown_users);
}

void	Commands::_cmd_names(void)
{
	std::vector<std::string> v;
	std::vector<Client *> tmp;
	std::vector<Client *> listed_users;
	std::vector<Client *> visible_users;
	std::map<std::string, std::string> m;
	Channel *channel;

	if (_message.arguments().size() >= 2 && _message.arguments(1) != _server->servername())
	{
		_message_user(_generate_reply(ERR_NOSUCHSERVER, "server name", _message.arguments(1)), _sender);
		return ;
	}
	if (_message.arguments().size() == 1 && _message.arguments(0) == _server->servername())
		_message.arguments().clear();
	if (!(_message.arguments().size()))
		for (channel_iterator it = _channels->begin(); it != _channels->end(); it++)
			v.push_back(it->first);
	else
		v = Message::split_commas(_message.arguments(0));
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
	{
		channel = _get_channel_by_name(*it);
		if (!channel || (!(channel->is_user(*_sender)) && ((channel->is_secret()) || (channel->is_private()))))
			continue ;
		if (channel->is_user(*_sender))
			tmp = __perform_names(*channel, true, (_message.arguments().size() ? true : false));
		else
			tmp = __perform_names(*channel, false, (_message.arguments().size() ? true : false));
		listed_users.insert(listed_users.end(), tmp.begin(), tmp.end());
	}
	if (_message.arguments().size())
		return ;
	for (client_iterator it = ++(_clients->begin()); it != _clients->end(); it++)
		if (!(it->second.is_invisible()) && std::find(listed_users.begin(), listed_users.end(), &(it->second)) == listed_users.end())
			visible_users.push_back(&(it->second));
	if (!(visible_users.size()))
	{
		if (!(_message.arguments().size()))
			m["channel"] = _server->servername();
		_message_user(_generate_reply(RPL_ENDOFNAMES, m), _sender);
		return ;
	}
	std::sort(visible_users.begin(), visible_users.end());
	for (std::vector<Client *>::iterator it = visible_users.begin(); it != visible_users.end(); it++)
		m["names_list"] += (*it)->nickname + ' ';	
	if (m["names_list"].size() && m["names_list"][m["names_list"].size() - 1] == ' ')
		m["names_list"].erase(m["names_list"].size() - 1);
	m["channel"] = '*';
	_message_user(_generate_reply(RPL_NAMREPLY, m), _sender);
	if (!(_message.arguments().size()))
		m["channel"] = _server->servername();
	_message_user(_generate_reply(RPL_ENDOFNAMES, m), _sender);
}
