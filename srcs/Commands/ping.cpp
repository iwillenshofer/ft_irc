/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:52 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:30:10 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.7.2 Ping message
**	Command: PING
**	Parameters: <server1> [ <server2> ]
**	
**	The PING command is used to test the presence of an active client or
**	server at the other end of the connection.  Servers send a PING
**	message at regular intervals if no other activity detected coming
**	from a connection.  If a connection fails to respond to a PING
**	message within a set amount of time, that connection is closed.  A
**	PING message MAY be sent even if the connection is active.
**	
**	When a PING message is received, the appropriate PONG message MUST be
**	sent as reply to <server1> (server which sent the PING message out)
**	as soon as possible.  If the <server2> parameter is specified, it
**	represents the target of the ping, and the message gets forwarded
**	there.
**	
**	Numeric Replies:
**			ERR_NOORIGIN                  ERR_NOSUCHSERVER
**	
**	Examples:
**	PING tolsun.oulu.fi             ; Command to send a PING message to
**									server
**	
**	PING WiZ tolsun.oulu.fi         ; Command from WiZ to send a PING
**									message to server "tolsun.oulu.fi"
**	
**	PING :irc.funet.fi              ; Ping message sent by server
**									"irc.funet.fi"
*/

void	Commands::_cmd_ping(void)
{

}
