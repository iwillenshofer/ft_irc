/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:21:33 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/30 11:26:06 by iwillens         ###   ########.fr       */
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
*/

void Commands::_cmd_connect(void)
{
	std::map<std::string, std::string> m;

	m["command"] = _message.command();
	if (!(_message.arguments().size()))
		_message_user(_generate_reply(ERR_NEEDMOREPARAMS, m), _sender);
	else if (!(_sender->is_operator()))
		_message_user(_generate_reply(ERR_NOPRIVILEGES, m), _sender);
	else if (_message.arguments()[0] != _server->servername())
	{
		m["server name"] = _message.arguments()[0];
		_message_user(_generate_reply(ERR_NOSUCHSERVER, m), _sender);
	}
}
