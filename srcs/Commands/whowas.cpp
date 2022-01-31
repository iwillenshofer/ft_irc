/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whowas.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:23 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/31 16:27:27 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.6.3 Whowas
**	Command: WHOWAS
**	Parameters: <nickname> *( "," <nickname> ) [ <count> [ <target> ] ]
**	
**	Whowas asks for information about a nickname which no longer exists.
**	This may either be due to a nickname change or the user leaving IRC.
**	In response to this query, the server searches through its nickname
**	history, looking for any nicks which are lexically the same (no wild
**	card matching here).  The history is searched backward, returning the
**	most recent entry first.  If there are multiple entries, up to
**	<count> replies will be returned (or all of them if no <count>
**	parameter is given).  If a non-positive number is passed as being
**	<count>, then a full search is done.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**			ERR_NONICKNAMEGIVEN           ERR_WASNOSUCHNICK
**			RPL_WHOWASUSER                RPL_WHOISSERVER
**			RPL_ENDOFWHOWAS
**	
**	Examples:
**	WHOWAS Wiz                      ; return all information in the nick
**									history about nick "WiZ";
**	
**	WHOWAS Mermaid 9                ; return at most, the 9 most recent
**									entries in the nick history for
**									"Mermaid";
**	
**	WHOWAS Trillian 1 *.edu         ; return the most recent history for
**									"Trillian" from the first server
**									found to match "*.edu".
*/

/*
** [IMPLEMENTATION NOTES]
** As there is only one server, the last parameter <target> is ignored.
** Whowas user is added when the user disconnects or changes nickname.
*/

void	Commands::_cmd_whowas(void)
{
	size_t i = 0;
	size_t max = 0;
	std::map<std::string, std::vector<Client> >::iterator it;
	std::map<std::string, std::string> m;
	std::vector<std::string> v;
	Debug("HERE");
	if (!(_message.arguments().size()))
	{
		_message_user(_generate_reply(ERR_NONICKNAMEGIVEN), _sender);
		return ;
	}
	if (_message.arguments().size() > 1 && ft::isNumeric(_message.arguments(1)))
		max = std::atoi(_message.arguments(1).c_str());
	Message::clear_commas(_message.arguments(0));
	v = ft::split(_message.arguments(0), ',');
	m["server"] = _server->servername();
	m["nickname"] = _message.arguments(0);
	for (std::vector<std::string>::iterator vit = v.begin(); vit != v.end(); vit++)
	{
		m["nick"] = *vit;
		it = _server->whowas().find(*vit);
		if (it == _server->whowas().end())
		{
			_message_user(_generate_reply(ERR_WASNOSUCHNICK, m), _sender);
			i++;
		}
		else
		{
			for (std::vector<Client>::iterator cit = _server->whowas()[*vit].begin(); cit != _server->whowas()[*vit].end(); cit++)
			{
				m["user"] = cit->username;
				m["host"] = cit->hostname;
				m["real_name"] = cit->realname;
				m["last_activity"] = ft::format_date(cit->last_ping);
				_message_user(_generate_reply(RPL_WHOWASUSER, m), _sender);
				_message_user(_generate_reply(RPL_WHOWASSERVER, m), _sender);
				if (max != 0 && i >= max)
					break ;
				i++;
			}
		}
		if (max != 0 && i >= max)
			break ;
	}
	_message_user(_generate_reply(RPL_ENDOFWHOWAS, m), _sender);
}
