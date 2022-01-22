/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:05 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/21 23:33:17 by iwillens         ###   ########.fr       */
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
	std::string error_msg;
	if (_message.arguments().size())
		error_msg = _message.arguments().back();
	else
		error_msg = SRV_DFLQUITMSG;
	std::string msg = _sender->get_prefix() + " QUIT :" + error_msg + MSG_ENDLINE;
	std::map<std::string, std::string> v;
	_message_all_channels(msg, false);
	for (std::map<std::string, Channel>::iterator it = _channels->begin(); it != _channels->end(); it++)
		it->second.remove_user(_sender->nickname);
	_sender->get_send_queue().clear();
	v["message"] = error_msg;
	_message_user(_generate_error(701, v), _sender);
	_sender->set_hangup(true);
}
