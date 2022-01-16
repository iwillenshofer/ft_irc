/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:17 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:30:26 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.1.3 User message
**	Command: USER
**	Parameters: <user> <mode> <unused> <realname>
**	
**	The USER command is used at the beginning of connection to specify
**	the username, hostname and realname of a new user.
**	
**	The <mode> parameter should be a numeric, and can be used to
**	automatically set user modes when registering with the server.  This
**	parameter is a bitmask, with only 2 bits having any signification: if
**	the bit 2 is set, the user mode 'w' will be set and if the bit 3 is
**	set, the user mode 'i' will be set.  (See Section 3.1.5 "User
**	Modes").
**	
**	The <realname> may contain space characters.
**	
**	Numeric Replies:
**			ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
**	
**	Example:
**	USER guest 0 * :Ronnie Reagan   ; User registering themselves with a
**									username of "guest" and real name
**									"Ronnie Reagan".
**	
**	USER guest 8 * :Ronnie Reagan   ; User registering themselves with a
**									username of "guest" and real name
**									"Ronnie Reagan", and asking to be set
**									invisible.
*/

void	Commands::_cmd_user(void)
{
	if (_sender.registered)
		_message_user(_generate_reply(ERR_ALREADYREGISTRED), _sender);
	else if (_message.arguments().size() < 4)
		_message_user(_generate_reply(ERR_NEEDMOREPARAMS), _sender);
	else
	{
		Debug("USER");
		_sender.realname = ft::trim(_message.arguments()[3]);
		if (_sender.realname.size() && _sender.realname[0] == ':')
			_sender.realname.erase(_sender.realname.begin());
		_sender.username = ft::trim(_message.arguments()[0]);
		_message.print();
		if (!(_sender.nickname.empty()))
			_register_user();
		else
			Debug(_sender.nickname, DBG_ERROR);
	}
}
