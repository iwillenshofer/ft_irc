/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:05 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/22 09:38:33 by iwillens         ###   ########.fr       */
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

/*
** [IMPLEMENTATION NOTES]
** The QUIT command is used by the User to quit itself from the server,
** or by the Server, to send a QUIT message on behalf of the user 
** to all other users that share a channel, upon disconnecting.
** If _sender->hangup() is set, the QUIT message was already sent to the user,
** so _cmd_quit() will just inform its peers.
** If not, it means that the QUIT user was initiated by the user, not the
** server, and _sender->hangup() will be set to true, which will communicate
** the peers only when the hangup is completed, with a QUIT message initiated
** by the Server.
*/

void	Commands::_cmd_quit(void)
{
	// must call _cmd_error() at the end.
	std::string error_msg;
	if (_message.arguments().size())
		error_msg = _message.arguments().back();
	else
		error_msg = SRV_DFLQUITMSG;
	if (_sender->get_hangup())
	{
		std::string msg = _sender->get_prefix() + " QUIT :" + error_msg + MSG_ENDLINE;
		_message_all_channels(msg, false);
	}
	else
	{
		_sender->set_hangup(true, "QUIT: " + error_msg);		
	}
}
