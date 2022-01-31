/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:19 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/31 15:38:28 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.4.3 Version message
**	Command: VERSION
**	Parameters: [ <target> ]
**	
**	The VERSION command is used to query the version of the server
**	program.  An optional parameter <target> is used to query the version
**	of the server program which a client is not directly connected to.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**			ERR_NOSUCHSERVER                RPL_VERSION
**	
**	Examples:
**	VERSION tolsun.oulu.fi          ; Command to check the version of
**									server "tolsun.oulu.fi".
*/

void	Commands::_cmd_version(void)
{
	std::map<std::string, std::string> m;
	Debug dbg;

	m["server"] = _server->servername();
	m["version"] = _server->version();
	m["debuglevel"] = dbg.debug_level();
	m["comments"] = SRV_COMMENTS;
	if (_message.arguments().size() && _message.arguments(0) != _server->servername())
	{
		m["server name"] = _message.arguments(0);
		_message_user(_generate_reply(ERR_NOSUCHSERVER, m), _sender);
	}
	else
		_message_user(_generate_reply(RPL_VERSION, m), _sender);
}
