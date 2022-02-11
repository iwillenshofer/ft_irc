/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:29:54 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/09 20:09:03 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.4.10 Info command
**	Command: INFO
**	Parameters: [ <target> ]
**	The INFO command is REQUIRED to return information describing the
**	server: its version, when it was compiled, the patchlevel, when it
**	was started, and any other miscellaneous information which may be
**	considered to be relevant.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**			ERR_NOSUCHSERVER
**			RPL_INFO                      RPL_ENDOFINFO
**	
**	Examples:
**	INFO csd.bu.edu                 ; request an INFO reply from
**									csd.bu.edu
**	
**	INFO Angel                      ; request info from the server that
**									Angel is connected to.
*/


// Test FT-IRC

// (irc op)
// /info                            > INFO OK
// /info test                   	> test :No such server
// /connect irc.42network.com       > INFO OK

// Test Undernet

// (irc op)
// /info                            > INFO OK
// /info test                   	> test :No such server
// /connect irc.42.ft       		> INFO OK

void	Commands::_cmd_info(void)
{
	std::map<std::string, std::string> m;
	std::vector<std::string> info;

	if (!(_message.arguments().size())
	|| (Message::is_bnf_nickname(_message.arguments(0)) && _get_client_by_nickname(_message.arguments(0)))
	|| (Mask::match_raw(_server->servername(), _message.arguments(0))))
	{
		info.push_back("ft_irc: A 42 Network project by @rbittet && @iwillens");
		info.push_back("Online since: " + ft::format_date(_server->creation_date()));
		for (std::vector<std::string>::iterator it = info.begin(); it != info.end(); it++)
		{
			m["string"] = *it;
			_message_user(_generate_reply(RPL_INFO, m), _sender);
		}
		_message_user(_generate_reply(RPL_ENDOFINFO, m), _sender);
	}
	else
	{
		m["server name"] = _message.arguments(0);
		_message_user(_generate_reply(ERR_NOSUCHSERVER, m), _sender);
	}
}
