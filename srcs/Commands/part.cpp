/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:48 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 22:14:44 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.2.2 Part message
**	Command: PART
**	Parameters: <channel> *( "," <channel> ) [ <Part Message> ]
**	
**	The PART command causes the user sending the message to be removed
**	from the list of active members for all given channels listed in the
**	parameter string.  If a "Part Message" is given, this will be sent
**	instead of the default message, the nickname.  This request is always
**	granted by the server.
**	
**	Servers MUST be able to parse arguments in the form of a list of
**	target, but SHOULD NOT use lists when sending PART messages to
**	clients.
**	
**	Numeric Replies:
**			ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
**			ERR_NOTONCHANNEL
**	
**	Examples:
**	PART #twilight_zone             ; Command to leave channel
**									"#twilight_zone"
**	
**	PART #oz-ops,&group5            ; Command to leave both channels
**									"&group5" and "#oz-ops".
**	
**	:WiZ!jto@tolsun.oulu.fi PART #playzone :I lost
**									; User WiZ leaving channel
**									"#playzone" with the message "I
**									lost".
*/

void	Commands::_cmd_part(void)
{
	Channel *channel;
	std::vector<std::string> v;
	if ((!_message.arguments().size()))
	{
		_message_user(_generate_reply(ERR_NEEDMOREPARAMS, "command", "PART"), _sender);
		return;
	}
	v = ft::split(_message.arguments(0), ',');
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
	{
		channel = _get_channel_by_name(*it);
		if ((!channel))
			_message_user(_generate_reply(ERR_NOSUCHCHANNEL, "channel name", *it), _sender);
		else if (!(channel->is_user(*_sender)))
			_message_user(_generate_reply(ERR_NOTONCHANNEL, "channel", *it), _sender);
		else
		{
			std::string msg = _sender->get_prefix() + " PART " + *it + MSG_ENDLINE;
			_message_channel(msg, *it, true);
			channel->remove_user(*_sender);
			if (channel->is_empty())
				_channels->erase(channel->get_name());
		}
	}
}
