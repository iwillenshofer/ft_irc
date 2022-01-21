/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:48 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:30:05 by iwillens         ###   ########.fr       */
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
	std::string msg = _sender.get_prefix() + " PART " + _message.arguments()[0] + MSG_ENDLINE;
	_message_channel(msg, _message.arguments()[0], true);
	_channels[_message.arguments()[0]].remove_user(_sender.nickname);
}