/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:25 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 21:59:44 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.6.2 Whois query
**	Command: WHOIS
**	Parameters: [ <target> ] <mask> *( "," <mask> )
**	
**	This command is used to query information about particular user.
**	The server will answer this command with several numeric messages
**	indicating different statuses of each user which matches the mask (if
**	you are entitled to see them).  If no wildcard is present in the
**	<mask>, any information about that nick which you are allowed to see
**	is presented.
**	
**	If the <target> parameter is specified, it sends the query to a
**	specific server.  It is useful if you want to know how long the user
**	in question has been idle as only local server (i.e., the server the
**	user is directly connected to) knows that information, while
**	everything else is globally known.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**			ERR_NOSUCHSERVER              ERR_NONICKNAMEGIVEN
**			RPL_WHOISUSER                 RPL_WHOISCHANNELS
**			RPL_WHOISCHANNELS             RPL_WHOISSERVER
**			RPL_AWAY                      RPL_WHOISOPERATOR
**			RPL_WHOISIDLE                 ERR_NOSUCHNICK
**			RPL_ENDOFWHOIS
**	
**	Examples:
**	WHOIS wiz                       ; return available user information
**									about nick WiZ
**	
**	WHOIS eff.org trillian          ; ask server eff.org for user
**									information  about trillian
*/

/*
** [TESTS DONE]
** /whois
** /whois unknown_nick
** /whois unmatching_mask
** /whois matching_mask
** /whois known_nick
** /whois invisible_user
** /whois invisible_user; while sharing channel
** /whois user1,user2,user3
** /whois user1,mask,mask
*/

void	Commands::__perform_whois(std::vector<std::string> &v, std::string &arguments)
{
	Client *client;
	std::vector<std::string>::iterator it = std::unique(v.begin(), v.end());
	std::map<std::string, std::string> m;
	v.resize(it - v.begin());
	m["server"] = _server->servername();
	m["server_info"] = std::string(MSG_NAME_SERVER);
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
	{
		client = _get_client_by_nickname(*it);
		if (client)
		{
			m["nick"] = client->nickname;
			m["user"] = client->username;
			m["host"] = client->hostname;
			m["real_name"] = client->realname;
			m["away message"] = client->away_message;
			m["secidle"] = ft::to_string(client->get_idle());
			m["channel_list"] = _channel_list(client);
			_message_user(_generate_reply(RPL_WHOISUSER, m), _sender);
			if (m["channel_list"].size())
				_message_user(_generate_reply(RPL_WHOISCHANNELS, m), _sender);
			_message_user(_generate_reply(RPL_WHOISSERVER, m), _sender);
			if (client->is_operator())
				_message_user(_generate_reply(RPL_WHOISOPERATOR, m), _sender);
			_message_user(_generate_reply(RPL_WHOISIDLE, m), _sender);
			if (client->is_away())
				_message_user(_generate_reply(RPL_AWAY, m), _sender);
		}
		else
		{
			m["nickname"] = *it;
			_message_user(_generate_reply(ERR_NOSUCHNICK, m), _sender);
		}
		if (it - v.begin() >= SRV_MAXWHOIS)
		{
			_message_user(_generate_reply(ERR_WHOISTOOMANY), _sender);
			break ;
		}
	}
	m["nick"] = arguments;
	_message_user(_generate_reply(RPL_ENDOFWHOIS, m), _sender);
}

void	Commands::_cmd_whois(void)
{
	std::vector<std::string> masks;
	std::vector<std::string> userlist;
	int first_arg = 0;

	if (!(_message.arguments().size()))
	{   
		_message_user(_generate_reply(ERR_NONICKNAMEGIVEN), _sender);
		return ;
	}
    if (_message.arguments().size() >= 2 && (_message.arguments(0) != _server->servername()))
    {
        _message_user(_generate_reply(ERR_NOSUCHSERVER, "server name", _message.arguments(0)), _sender);
        return ;
    }
    if (_message.arguments().size() >= 2)
	    first_arg = 1;
	masks = ft::split(_message.arguments(first_arg), ',');
	for (std::vector<std::string>::iterator it = masks.begin(); it != masks.end(); it++)
	{
		if (!(Message::has_bnf_wildcard(*it)) && !(_get_client_by_nickname(*it)))
		{
			_message_user(_generate_reply(ERR_NOSUCHNICK, "nickname", *it), _sender);
			continue ;
		}
		for (std::map<int, Client>::iterator mit = ++(_clients->begin()); mit != _clients->end(); mit++)
		{
			if (Mask::match_raw(mit->second.nickname, *it)
			&& (std::find(userlist.begin(), userlist.end(), mit->second.nickname) == userlist.end())
			&& (!(mit->second.is_invisible()) || _shared_channel(&(mit->second), _sender) || (&(mit->second) == _sender)))
				userlist.push_back(mit->second.nickname);
		}
	}
	__perform_whois(userlist, _message.arguments(first_arg));
}
