/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:21:33 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/09 20:04:35 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**4.3.5 Connect message
**
**Command: CONNECT
**Parameters: <target server> [<port> [<remote server>]]
**
**The CONNECT command can be used to force a server to try to establish
**a new connection to another server immediately.  CONNECT is a
**privileged command and is to be available only to IRC Operators.  If
**a remote server is given then the CONNECT attempt is made by that
**server to <target server> and <port>.
**
**Numeric Replies:
**        ERR_NOSUCHSERVER                ERR_NOPRIVILEGES
**        ERR_NEEDMOREPARAMS
**
**Examples:
**CONNECT tolsun.oulu.fi          ; Attempt to connect a server to
**                                tolsun.oulu.fi
** [IMPLEMENTATION NOTES]
** as there is no server-server communication, this command
** only verifies the required parameters.
*/

// Test FT-IRC

// (irc op)
// /connect                         > Connect :Not enough parameters
// /connect test1                   > Connect: Host test1 is not listed.
// /connect test1 test2             > Connect: Host test1 is not listed.
// /connect test1 test2 test3       > test3 :No such server
// /connect test1 test2 irc.42network.com       > Connect: Host test1 is not listed.

// (Not irc op)
// /connect                         > Permission Denied- You're not an IRC operator
// /connect test1                   > Permission Denied- You're not an IRC operator
// /connect test1 test2             > Permission Denied- You're not an IRC operator
// /connect test1 test2 test3       > Permission Denied- You're not an IRC operator
// /connect test1 test2 irc.42network.com       > Permission Denied- You're not an IRC operator

// Test Undernet

// (irc op)
// /connect                         > Connect :Not enough parameters
// /connect test1                   > Connect: Host test1 is not listed.
// /connect test1 test2             > Connect: Host test1 is not listed.
// /connect test1 test2 test3       > test3 :No such server
// /connect test1 test2 irc.42.ft   > Connect: Host test1 is not listed.

// (Not irc op)

// /connect                         > Permission Denied: Insufficient privileges
// /connect test1                   > Permission Denied: Insufficient privileges
// /connect test1 test2             > Permission Denied: Insufficient privileges
// /connect test1 test2 test3       > Permission Denied: Insufficient privileges
// /connect test1 test2 irc.42.ft   > Permission Denied: Insufficient privileges


void Commands::_cmd_connect(void)
{
	if (!(_sender->is_operator()))
		_message_user(_generate_reply(ERR_NOPRIVILEGES, "", ""), _sender);
	else if (!(_message.arguments().size()))
		_message_user(_generate_reply(ERR_NEEDMOREPARAMS, "command", _message.command()), _sender);
	else if (_message.arguments().size() >= 3 && _message.arguments(2) != _server->servername())
		_message_user(_generate_reply(ERR_NOSUCHSERVER, "server name", _message.arguments(2)), _sender);
	else
	{
		std::string msg = ":" + _server->servername() + " NOTICE " + _sender->nickname + " :";
		msg += "Connect: Host " + _message.arguments(0) + " is not listed." + MSG_ENDLINE;  
		_message_user(msg, _sender);
	}
}
