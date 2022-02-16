/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:12 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 22:48:48 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.1.5 User mode message
**	Command: MODE
**	Parameters: <nickname>
**				*( ( "+" / "-" ) *( "i" / "w" / "o" / "O" / "r" ) )
**	
**	The user MODE's are typically changes which affect either how the
**	client is seen by others or what 'extra' messages the client is sent.
**	
**	A user MODE command MUST only be accepted if both the sender of the
**	message and the nickname given as a parameter are both the same.  If
**	no other parameter is given, then the server will return the current
**	settings for the nick.
**	
**		The available modes are as follows:
**	
**			a - user is flagged as away;
**			i - marks a users as invisible;
**			w - user receives wallops;
**			r - restricted user connection;
**			o - operator flag;
**			O - local operator flag;
**			s - marks a user for receipt of server notices.
**	
**	Additional modes may be available later on.
**	
**	The flag 'a' SHALL NOT be toggled by the user using the MODE command,
**	instead use of the AWAY command is REQUIRED.
**	
**	If a user attempts to make themselves an operator using the "+o" or
**	"+O" flag, the attempt SHOULD be ignored as users could bypass the
**	authentication mechanisms of the OPER command.  There is no
**	restriction, however, on anyone `deopping' themselves (using "-o" or
**	"-O").
**	
**	On the other hand, if a user attempts to make themselves unrestricted
**	using the "-r" flag, the attempt SHOULD be ignored.  There is no
**	restriction, however, on anyone `deopping' themselves (using "+r").
**	This flag is typically set by the server upon connection for
**	administrative reasons.  While the restrictions imposed are left up
**	to the implementation, it is typical that a restricted user not be
**	allowed to change nicknames, nor make use of the channel operator
**	status on channels.
**	
**	The flag 's' is obsolete but MAY still be used.
**	
**	Numeric Replies:
**			ERR_NEEDMOREPARAMS              ERR_USERSDONTMATCH
**			ERR_UMODEUNKNOWNFLAG            RPL_UMODEIS
**	
**	Examples:
**	MODE WiZ -w                     ; Command by WiZ to turn off
**									reception of WALLOPS messages.
**	
**	MODE Angel +i                   ; Command from Angel to make herself
**									invisible.
**	
**	MODE WiZ -o                     ; WiZ 'deopping' (removing operator
**									status).
*/

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.2.3 Channel mode message
**	Command: MODE
**	Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
**	
**	The MODE command is provided so that users may query and change the
**	characteristics of a channel.  For more details on available modes
**	and their uses, see "Internet Relay Chat: Channel Management" [IRC-
**	CHAN].  Note that there is a maximum limit of three (3) changes per
**	command for modes that take a parameter.
**	
**	Numeric Replies:
**			ERR_NEEDMOREPARAMS              ERR_KEYSET
**			ERR_NOCHANMODES                 ERR_CHANOPRIVSNEEDED
**			ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
**			RPL_CHANNELMODEIS
**			RPL_BANLIST                     RPL_ENDOFBANLIST
**			RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
**			RPL_INVITELIST                  RPL_ENDOFINVITELIST
**			RPL_UNIQOPIS
**	
**	The following examples are given to help understanding the syntax of
**	the MODE command, but refer to modes defined in "Internet Relay Chat:
**	Channel Management" [IRC-CHAN].
**	
**	Examples:
**	MODE #Finnish +imI *!*@*.fi     ; Command to make #Finnish channel
**									moderated and 'invite-only' with user
**									with a hostname matching *.fi
**									automatically invited.
**	
**	MODE #Finnish +o Kilroy         ; Command to give 'chanop' privileges
**									to Kilroy on channel #Finnish.
**	
**	MODE #Finnish +v Wiz            ; Command to allow WiZ to speak on
**									#Finnish.
**	
**	MODE #Fins -s                   ; Command to remove 'secret' flag
**									from channel #Fins.
**	
**	MODE #42 +k oulu                ; Command to set the channel key to
**									"oulu".
**	
**	MODE #42 -k oulu                ; Command to remove the "oulu"
**									channel key on channel "#42".
**	
**	MODE #eu-opers +l 10            ; Command to set the limit for the
**									number of users on channel
**									"#eu-opers" to 10.
**	
**	:WiZ!jto@tolsun.oulu.fi MODE #eu-opers -l
**									; User "WiZ" removing the limit for
**									the number of users on channel "#eu-
**									opers".
**	
**	MODE &oulu +b                   ; Command to list ban masks set for
**									the channel "&oulu".
**	P
**	MODE &oulu +b *!*@*             ; Command to prevent all users from
**									joining.
**	
**	MODE &oulu +b *!*@*.edu +e *!*@*.bu.edu
**									; Command to prevent any user from a
**									hostname matching *.edu from joining,
**									except if matching *.bu.edu
**	
**	MODE #bu +be *!*@*.edu *!*@*.bu.edu
**									; Comment to prevent any user from a
**									hostname matching *.edu from joining,
**									except if matching *.bu.edu
**	
**	MODE #meditation e              ; Command to list exception masks set
**									for the channel "#meditation".
**	
**	MODE #meditation I              ; Command to list invitations masks
**									set for the channel "#meditation".
**	
**	MODE !12345ircd O               ; Command to ask who the channel
**									creator for "!12345ircd" is
*/

void	Commands::_cmd_mode(void)
{
	if (_message.arguments(0).at(0) == '#' || _message.arguments(0).at(0) == '&')
		_cmd_mode_channel();
	else
		_cmd_mode_user();
}
