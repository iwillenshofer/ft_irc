/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 12:54:29 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/30 13:20:59 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
** 4.1.4 Server message
** Command: SERVER
** Parameters: <servername> <hopcount> <info>
** 
** The server message is used to tell a server that the other end of a
** new connection is a server. This message is also used to pass server
** data over whole net.  When a new server is connected to net,
** information about it be broadcast to the whole network.  <hopcount>
** is used to give all servers some internal information on how far away
** all servers are.  With a full server list, it would be possible to
** construct a map of the entire server tree, but hostmasks prevent this
** from being done.
** 
** The SERVER message must only be accepted from either (a) a connection
** which is yet to be registered and is attempting to register as a
** server, or (b) an existing connection to another server, in  which
** case the SERVER message is introducing a new server behind that
** server.
** 
** Most errors that occur with the receipt of a SERVER command result in
** the connection being terminated by the destination host (target
** SERVER).  Error replies are usually sent using the "ERROR" command
** rather than the numeric since the ERROR command has several useful
** properties which make it useful here.
** 
** If a SERVER message is parsed and attempts to introduce a server
** which is already known to the receiving server, the connection from
** which that message must be closed (following the correct procedures),
** since a duplicate route to a server has formed and the acyclic nature
** of the IRC tree broken.
** 
** Numeric Replies:
**          ERR_ALREADYREGISTRED
** 
** Example:
** SERVER test.oulu.fi 1 :[tolsun.oulu.fi] Experimental server
**                                 ; New server test.oulu.fi introducing
**                                 itself and attempting to register.  The
**                                 name in []'s is the hostname for the
**                                 host running test.oulu.fi.
** 
** 
** :tolsun.oulu.fi SERVER csd.bu.edu 5 :BU Central Server
**                                 ; Server tolsun.oulu.fi is our uplink
**                                 for csd.bu.edu which is 5 hops away.
** [IMPLEMENTATION NOTES]
** This command takes no actions, as server-server communication is not implemented.
*/

void	Commands::_cmd_server(void)
{
	std::map<std::string, std::string> m;

	m["command"] = _message.command();
 	if ((_message.arguments().size()) < 3)
		_message_user(_generate_reply(ERR_NEEDMOREPARAMS, m), _sender);
	else if (_sender->registered)
		_message_user(_generate_reply(ERR_ALREADYREGISTRED), _sender);
}
