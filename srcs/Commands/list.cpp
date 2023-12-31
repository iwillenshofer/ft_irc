/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:07 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/16 22:35:02 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.2.6 List message
**	Command: LIST
**	Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
**	
**	The list command is used to list channels and their topics.  If the
**	<channel> parameter is used, only the status of that channel is
**	displayed.
**	
**	If the <target> parameter is specified, the request is forwarded to
**	that server which will generate the reply.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**	
**			ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
**			RPL_LIST                        RPL_LISTEND
**	
**	Examples:
**	
**	LIST                            ; Command to list all channels.
**	
**	LIST #twilight_zone,#42         ; Command to list channels
**									#twilight_zone and #42
**
** [IMPLEMENTATION NOTES]
** As we are not doing server-server communication, target argument
** is ignored.
*/

void	Commands::__perform_list(Channel &channel)
{
	size_t visible = 0;
	std::map<std::string, std::string> m;

	if (!(channel.is_user(*_sender)) && (channel.is_private() || channel.is_secret()))
		return ;
	if (channel.is_user(*_sender))
		visible = channel.users.size();
	else
	{
		for (std::vector<Client *>::iterator it = channel.users.begin(); it != channel.users.end(); it++)
			if (!((*it)->is_invisible()) || _shared_channel(_sender, *it))
				visible++;
	}
	m["channel"] = channel.get_name();
	m["visible"] = ft::to_string(visible);
	m["topic"] = channel.get_topic();
	_message_user(_generate_reply(RPL_LIST, m), _sender);
}

void	Commands::_cmd_list(void)
{
	std::vector<std::string> v;
	Channel *channel;

	if (_message.arguments().size() > 1 && !(Mask::match_raw(_server->servername(), _message.arguments(1))))
	{
		_message_user(_generate_reply(ERR_NOSUCHSERVER, "server name", _message.arguments(1)), _sender);
		return ;
	}
	if (!(_message.arguments().size()))
	{
		for (channel_iterator it = _channels->begin(); it != _channels->end(); it++)
			__perform_list(it->second);
	}	
	else
	{
		v = Message::split_commas(_message.arguments(0), true);		
		for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
		{
			channel = _get_channel_by_name(*it);
			if (channel)
				__perform_list(*channel);
		}
	}
	_message_user(_generate_reply(RPL_LISTEND), _sender);
}
