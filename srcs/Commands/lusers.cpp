/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lusers.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:10 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/17 22:44:19 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.4.2 Lusers message
**	Command: LUSERS
**	Parameters: [ <mask> [ <target> ] ]
**	
**	The LUSERS command is used to get statistics about the size of the
**	IRC network.  If no parameter is given, the reply will be about the
**	whole net.  If a <mask> is specified, then the reply will only
**	concern the part of the network formed by the servers matching the
**	mask.  Finally, if the <target> parameter is specified, the request
**	is forwarded to that server which will generate the reply.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**	
**			RPL_LUSERCLIENT                 RPL_LUSEROP
**			RPL_LUSERUNKOWN                 RPL_LUSERCHANNELS
**			RPL_LUSERME                     ERR_NOSUCHSERVER
*/

void	Commands::_cmd_lusers(void)
{
	int users = 0;
	int invisible = 0;
	int operators = 0;
	std::map<std::string, std::string> m;

	if (_message.arguments().size() >= 1 && !(Mask::match_raw(_server->servername(), _message.arguments(0))))
	{
		_message_user(_generate_reply(ERR_NOSUCHSERVER, "server name", _message.arguments(0)), _sender);
		return ;
	}	
	if (_message.arguments().size() >= 2 && _server->servername() != _message.arguments(1))
	{
		_message_user(_generate_reply(ERR_NOSUCHSERVER, "server name", _message.arguments(1)), _sender);
		return ;
	}
	for (std::map<int, Client>::iterator it = ++(_clients->begin()); it != _clients->end(); it++ )
	{
		if (it->second.is_operator())
			operators++;
		if (it->second.is_invisible())
			invisible++;
		else
			users++;
	}
	m["intusers"] = ft::to_string(users);
	m["intinvisible"] = ft::to_string(invisible);
	m["intservers"] = ft::to_string(1);
	m["intoper"] = ft::to_string(operators);
	m["intclients"] = ft::to_string(_clients->size() - 1);
	m["intchannels"] = ft::to_string(_channels->size());
	_message_user(_generate_reply(RPL_LUSERCLIENT, m), _sender);
	_message_user(_generate_reply(RPL_LUSEROP, m), _sender);
	_message_user(_generate_reply(RPL_LUSERCHANNELS, m), _sender);
	_message_user(_generate_reply(RPL_LUSERME, m), _sender);
}
