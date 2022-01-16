/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:03 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:31:20 by iwillens         ###   ########.fr       */
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

void	Commands::_cmd_privmsg(void)
{
	std::string destination = _message.arguments().front();
	std::string msg = _sender.get_prefix() + " PRIVMSG " + _message.arguments().front() + " " + _message.arguments().back() + MSG_ENDLINE;

	if (destination.at(0) == '#')
		_message_channel(msg, _message.arguments().front(), false);
	else
		_message_user(msg, _message.arguments().front());
}
