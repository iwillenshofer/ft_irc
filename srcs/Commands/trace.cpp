/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:15 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/30 12:49:02 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.4.8 Trace message
**	Command: TRACE
**	Parameters: [ <target> ]
**	
**	TRACE command is used to find the route to specific server and
**	information about its peers.  Each server that processes this command
**	MUST report to the sender about it.  The replies from pass-through
**	links form a chain, which shows route to destination.  After sending
**	this reply back, the query MUST be sent to the next server until
**	given <target> server is reached.
**	
**	TRACE command is used to find the route to specific server.  Each
**	server that processes this message MUST tell the sender about it by
**	sending a reply indicating it is a pass-through link, forming a chain
**	of replies.  After sending this reply back, it MUST then send the
**	TRACE message to the next server until given server is reached.  If
**	the <target> parameter is omitted, it is RECOMMENDED that TRACE
**	command sends a message to the sender telling which servers the local
**	server has direct connection to.
**	
**	If the destination given by <target> is an actual server, the
**	destination server is REQUIRED to report all servers, services and
**	operators which are connected to it; if the command was issued by an
**	operator, the server MAY also report all users which are connected to
**	it.  If the destination given by <target> is a nickname, then only a
**	reply for that nickname is given.  If the <target> parameter is
**	omitted, it is RECOMMENDED that the TRACE command is parsed as
**	targeted to the processing server.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**			ERR_NOSUCHSERVER
**	
**		If the TRACE message is destined for another server, all
**		intermediate servers must return a RPL_TRACELINK reply to indicate
**		that the TRACE passed through it and where it is going next.
**	
**			RPL_TRACELINK
**	
**		A TRACE reply may be composed of any number of the following
**		numeric replies.
**	
**			RPL_TRACECONNECTING           RPL_TRACEHANDSHAKE
**			RPL_TRACEUNKNOWN              RPL_TRACEOPERATOR
**			RPL_TRACEUSER                 RPL_TRACESERVER
**			RPL_TRACESERVICE              RPL_TRACENEWTYPE
**			RPL_TRACECLASS                RPL_TRACELOG
**			RPL_TRACEEND
**	
**	Examples:
**	TRACE *.oulu.fi                 ; TRACE to a server matching
**									*.oulu.fi
**
** As there is no implementation of server-server communication, 
** the trace commands will not match other servers.
** Just like in UnderNet, it is limited to operators.
*/

void	Commands::__perform_trace(Client &client, std::map<std::string, std::string> &m)
{
	m["nick"] = client.nickname;
	if (client.is_operator())
	{
		m["class"] = "Oper";
		_message_user(_generate_reply(RPL_TRACEOPERATOR, m), _sender);
	}
	else
	{
		m["class"] = "Local";
		_message_user(_generate_reply(RPL_TRACEUSER, m), _sender);
	}
}

void	Commands::_cmd_trace(void)
{
	std::map<std::string, std::string> m;
	std::string mask;
	bool found = false;
	size_t user = 0;
	size_t oper = 0;
	Debug dbg;

	if (!(_sender->is_operator()))
	{
		_message_user(_generate_reply(ERR_NOPRIVILEGES, m), _sender);
		return ;
	}
	if (!(_message.arguments().size()))
		mask = "*";
	else
		mask = _message.arguments()[0];
	if (Mask::match_raw(_server->servername(), mask))
	{
		found = true;
		for (client_iterator it = ++(_clients->begin()); it != _clients->end(); it++)
		{
			__perform_trace(it->second, m);
			if (it->second.is_operator()) oper++;
			user++;
		}
		m["class"] = "Oper";
		m["count"] = ft::to_string(oper);
		_message_user(_generate_reply(RPL_TRACECLASS, m), _sender);
		m["class"] = "Local";			
		m["count"] = ft::to_string(user);
		_message_user(_generate_reply(RPL_TRACECLASS, m), _sender);
	}
	else
	{
		for (client_iterator it = ++(_clients->begin()); it != _clients->end(); it++)
		{
			if (Mask::match_raw(it->second.nickname, mask))
			{
				found = true;
				__perform_trace(it->second, m);
			}
		}
	}
	m["server name"] = mask;
	if (!(found))
		_message_user(_generate_reply(ERR_NOSUCHSERVER, m), _sender);
	else
	{
		m["server_name"] = _server->servername();
		m["version"] = _server->version();
		m["debug_level"] = dbg.debug_level();
		_message_user(_generate_reply(RPL_TRACEEND, m), _sender);
	}
}
