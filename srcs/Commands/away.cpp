/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 21:40:27 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 22:12:13 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**   Command: AWAY
**   Parameters: [ <text> ]
**
**   With the AWAY command, clients can set an automatic reply string for
**   any PRIVMSG commands directed at them (not to a channel they are on).
**   The server sends an automatic reply to the client sending the PRIVMSG
**   command.  The only replying server is the one to which the sending
**   client is connected to.
**
**   The AWAY command is used either with one parameter, to set an AWAY
**   message, or with no parameters, to remove the AWAY message.
**
**   Because of its high cost (memory and bandwidth wise), the AWAY
**   message SHOULD only be used for client-server communication.  A
**   server MAY choose to silently ignore AWAY messages received from
**   other servers.  To update the away status of a client across servers,
**   the user mode 'a' SHOULD be used instead.  (See Section 3.1.5)
**
**   Numeric Replies:
**           RPL_UNAWAY                    RPL_NOWAWAY
**
**   Example:
**   AWAY :Gone to lunch.  Back in 5 ; Command to set away message to
**                                   "Gone to lunch.  Back in 5".
*/

void	Commands::_cmd_away(void)
{
	if (!(_message.arguments().size()))
	{
		_sender->away_message = "";
		_sender->unset_away();
		_message_user(_generate_reply(RPL_UNAWAY), _sender);
	}
	else
	{
		_sender->away_message = _message.arguments(0);
		_sender->set_away();
		_message_user(_generate_reply(RPL_NOWAWAY), _sender);
	}

}
