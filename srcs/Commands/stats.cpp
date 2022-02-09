/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:09 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/08 21:45:21 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.4.4 Stats message
**	Command: STATS
**	Parameters: [ <query> [ <target> ] ]
**	
**	The stats command is used to query statistics of certain server.  If
**	<query> parameter is omitted, only the end of stats reply is sent
**	back.
**	
**	A query may be given for any single letter which is only checked by
**	the destination server and is otherwise passed on by intermediate
**	servers, ignored and unaltered.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Except for the ones below, the list of valid queries is
**	implementation dependent.  The standard queries below SHOULD be
**	supported by the server:
**	
**			l - returns a list of the server's connections, showing how
**				long each connection has been established and the
**				traffic over that connection in Kbytes and messages for
**				each direction;
**			m - returns the usage count for each of commands supported
**				by the server; commands for which the usage count is
**				zero MAY be omitted;
**			o - returns a list of configured privileged users,
**				operators;
**			u - returns a string showing how long the server has been
**				up.
**	
**	It is also RECOMMENDED that client and server access configuration be
**	published this way.
**	
**	Numeric Replies:
**			ERR_NOSUCHSERVER
**			RPL_STATSLINKINFO                RPL_STATSUPTIME
**			RPL_STATSCOMMANDS                RPL_STATSOLINE
**			RPL_ENDOFSTATS
**	
**	Examples:
**	STATS m                         ; Command to check the command usage
**									for the server you are connected to
** [IMPLEMENTATION NOTES]
** Although undernet limits the l,m and o commands only to operators,
**  we chose not to, as it is not specified in the RFC.
** No link information is provided, as there are no server connections.
*/

void	Commands::_cmd_stats(void)
{
	std::map<std::string, std::string> m;
	std::string valid(MSG_ALLOWEDSTATS);
	char cmd;
	size_t diff;

	m["stats_letter"] = "*";
	if (!(_message.arguments().size()) || _message.arguments(0).size() != 1
	|| valid.find(_message.arguments(0)[0]) == std::string::npos)
	{
		_message_user(_generate_reply(RPL_ENDOFSTATS, m), _sender);
		return ;
	}
	cmd = _message.arguments(0)[0];
	m["stats_letter"] = cmd;
	if (cmd == 'm')
	{
		for (std::map<std::string, size_t>::iterator it = _server->commandstats().begin(); it != _server->commandstats().end(); it++)
		{
			m["command"] = it->first;
			m["count"] = ft::to_string(it->second);
			_message_user(_generate_reply(RPL_STATSCOMMANDS, m), _sender);
		}
	}
	else if (cmd == 'o')
	{
		for (std::map<std::string, unsigned long>::iterator it = _server->operators().begin(); it != _server->operators().end(); it++)
		{
			m["hostmask"] = Mask::create("*");
			m["name"] = it->first;
			_message_user(_generate_reply(RPL_STATSOLINE, m), _sender);
		}
	}
	else if (cmd == 'u')
	{
		diff = static_cast<size_t>(std::difftime(time(NULL), _server->creation_date()));
		m["days"] = ft::to_string(diff / (60 * 60 * 24));
		m["hours"] = ft::to_string((diff / (60 * 60)) % 24);
		m["minutes"] = ft::to_string((diff / 60) % (60));
		m["seconds"] = ft::to_string((diff) % (60));
		if (m["minutes"].size() == 1) m["minutes"] = "0" + m["minutes"];
		if (m["seconds"].size() == 1) m["seconds"] = "0" + m["seconds"];
		_message_user(_generate_reply(RPL_STATSUPTIME, m), _sender);
	}
	_message_user(_generate_reply(RPL_ENDOFSTATS, m), _sender);
}
