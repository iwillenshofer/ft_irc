/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:05 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/31 15:38:28 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.4.5 Links message
**	Command: LINKS
**	Parameters: [ [ <remote server> ] <server mask> ]
**	
**	With LINKS, a user can list all servernames, which are known by the
**	server answering the query.  The returned list of servers MUST match
**	the mask, or if no mask is given, the full list is returned.
**	
**	If <remote server> is given in addition to <server mask>, the LINKS
**	command is forwarded to the first server found that matches that name
**	(if any), and that server is then required to answer the query.
**	
**	Numeric Replies:
**	
**			ERR_NOSUCHSERVER
**			RPL_LINKS                        RPL_ENDOFLINKS
**	
**	Examples:
**	
**	LINKS *.au                      ; Command to list all servers which
**									have a name that matches *.au;
**	
**	LINKS *.edu *.bu.edu            ; Command to list servers matching
**									*.bu.edu as seen by the first server
**									matching *.edu.
** [IMPLEMENTATION NOTES]
** as there are no server-server communication, only returns the local
** server. Second argument is ignored.
*/

void	Commands::_cmd_links(void)
{
	std::string mask;
	std::map<std::string, std::string> m;

	mask = (_message.arguments().size() ? _message.arguments(0) : std::string("*"));
	m["mask"] = mask;
	if (Mask::match_raw(_server->servername(), mask))
	{
		m["server"] = _server->servername();
		m["server_info"] = std::string(MSG_NAME_SERVER);
		m["hopcount"] = ft::to_string(0);
		_message_user(_generate_reply(RPL_LINKS, m), _sender);
	}
	_message_user(_generate_reply(RPL_ENDOFLINKS, m), _sender);
}
