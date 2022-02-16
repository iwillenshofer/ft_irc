/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:29:54 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 20:25:09 by roman            ###   ########.fr       */
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

void	Commands::_cmd_info(void)
{
	std::vector<std::string> info;

	if ((_message.arguments().size() == 0)
		|| ((Mask::match_raw(_server->servername(), _message.arguments(0)))
		&& (_sender->is_operator() == true)))
	{
		info.push_back("ft_irc: A 42 Network project by @rbittet && @iwillens");
		info.push_back("Online since: " + ft::format_date(_server->creation_date()));
		for (std::vector<std::string>::iterator it = info.begin(); it != info.end(); it++)
			_message_user(_generate_reply(RPL_INFO, "string", *it), _sender);
		_message_user(_generate_reply(RPL_ENDOFINFO, "", ""), _sender);
	}
	else if (_sender->is_operator() == false)
		_message_user(_generate_reply(ERR_NOPRIVILEGES, "", ""), _sender);
	else
		_message_user(_generate_reply(ERR_NOSUCHSERVER, "server name", _message.arguments(0)), _sender);
}
