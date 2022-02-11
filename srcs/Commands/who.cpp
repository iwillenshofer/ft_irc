/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:21 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/10 21:21:42 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.6.1 Who query
**	Command: WHO
**	Parameters: [ <mask> [ "o" ] ]
**	
**	The WHO command is used by a client to generate a query which returns
**	a list of information which 'matches' the <mask> parameter given by
**	the client.  In the absence of the <mask> parameter, all visible
**	(users who aren't invisible (user mode +i) and who don't have a
**	common channel with the requesting client) are listed.  The same
**	result can be achieved by using a <mask> of "0" or any wildcard which
**	will end up matching every visible user.
**	
**	The <mask> passed to WHO is matched against users' host, server, real
**	name and nickname if the channel <mask> cannot be found.
**	
**	If the "o" parameter is passed only operators are returned according
**	to the <mask> supplied.
**	
**	Numeric Replies:
**	
**			ERR_NOSUCHSERVER
**			RPL_WHOREPLY                  RPL_ENDOFWHO
**	
**	Examples:
**	
**	WHO *.fi                        ; Command to list all users who match
**									against "*.fi".
**	
**	WHO jto* o                      ; Command to list all users with a
**									match against "jto*" if they are an
**									operator.
**
** 352     RPL_WHOREPLY
**                        "<channel> <user> <host> <server> <nick> \
**                         <H|G>[*][@|+] :<hopcount> <real name>"
*/

void Commands::__perform_who(Client &client, std::map<std::string, std::string> &arguments, Channel *channel)
{
	arguments["channel"] = (channel ? channel->get_name() : "*");
	arguments["user"] = client.username;
	arguments["host"] = client.hostname;
	arguments["nick"] = client.nickname;
	arguments["real_name"] = client.realname;
	arguments["away"] = (client.is_away() ? "G" : "H");
	arguments["servop"] = (client.is_operator() ? "*" : "");
	arguments["chanop"] = "";
	if (channel && channel->is_operator(client))
		arguments["chanop"] = "@";
	else if (channel && channel->is_voice(client))
		arguments["chanop"] = "+";
	arguments["hops"] = "0";
	_message_user(_generate_reply(RPL_WHOREPLY, arguments), _sender);
}


void	Commands::_cmd_who(void)
{
	std::map<std::string, std::string> arguments;
	std::vector<Client *> shared_channel;
	Channel *channel;
	int include_invisible = false;

	if (!(_message.arguments().size()))
		_message.arguments().push_back("*");
	else if (_message.arguments(0) == "0")
		_message.arguments(0) = "*";
	arguments["name"] = _message.arguments(0);
	arguments["server"] = _server->servername();
	if (Message::is_bnf_channel(_message.arguments(0)))
	{
		channel = _get_channel_by_name(_message.arguments(0));
		if ((channel) && !(channel->is_secret()))
		{
			if (channel->is_user(*_sender))
				include_invisible = true;
			for (std::vector<Client *>::iterator it = channel->users.begin(); it != channel->users.end(); it++)
			{
				if ((include_invisible || (!((*it)->is_invisible()))))
					__perform_who(**it, arguments, channel);
			}
		}
	}
	else
	{
		for (client_iterator it = ++(_clients->begin()); it != _clients->end(); it++)
		{
			if ((!(it->second.is_invisible()) || _shared_channel(&(it->second), _sender))
			&& (Mask::match(it->second, _message.arguments(0)) || Mask::match_raw(it->second.nickname, _message.arguments(0))
			|| Mask::match_raw(it->second.hostname, _message.arguments(0)) || Mask::match_raw(it->second.realname, _message.arguments(0))
			|| Mask::match_raw(_server->servername(), _message.arguments(0))))
			{
				if (_message.arguments().size() <= 1 || _message.arguments(1) != "o" || it->second.is_operator())
					__perform_who(it->second, arguments);
			}
		}
	}
	_message_user(_generate_reply(RPL_ENDOFWHO, arguments), _sender);
}
