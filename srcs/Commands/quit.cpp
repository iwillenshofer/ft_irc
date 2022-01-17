/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:05 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:30:18 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.1.7 Quit
**	Command: QUIT
**	Parameters: [ <Quit Message> ]
**	
**	A client session is terminated with a quit message.  The server
**	acknowledges this by sending an ERROR message to the client.
**	
**	Numeric Replies:
**			None.
**	
**	Example:
**	QUIT :Gone to have lunch        ; Preferred message format.
**	
**	:syrk!kalt@millennium.stealth.net QUIT :Gone to have lunch ; User
**									syrk has quit IRC to have lunch.
*/

void	Commands::_cmd_quit(void)
{
	// must call _cmd_error() at the end.
	std::string msg = _sender.get_prefix() + " QUIT " + _message.arguments().back() + MSG_ENDLINE;
	_message_all_channels(msg, false);
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); it++)
		it->second.remove_user(_sender.nickname);
	_sender.set_hangup(true);
}
