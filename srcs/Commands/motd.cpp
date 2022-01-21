/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:14 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/21 15:30:41 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.4.1 Motd message
**	Command: MOTD
**	Parameters: [ <target> ]
**	
**	The MOTD command is used to get the "Message Of The Day" of the given
**	server, or current server if <target> is omitted.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**			RPL_MOTDSTART                   RPL_MOTD
**			RPL_ENDOFMOTD                   ERR_NOMOTD
*/

void	Commands::_cmd_motd(void)
{
	std::string s;
	std::map<std::string, std::string> v;
	std::vector<std::string> lst;

	try
	{
		s = ft::load_file(_server->motdfilename());
	}
	catch(const std::exception& e)
	{
		_message_user(_generate_reply(ERR_NOMOTD), _sender);
		return ;
	}
	lst = ft::split(s, '\n');
	v["server"] = _server->servername();
	_message_user(_generate_reply(RPL_MOTDSTART, v), _sender);
	for (std::vector<std::string>::iterator it = lst.begin(); it != lst.end(); it++)
	{
		v["text"] = *it;
		_message_user(_generate_reply(RPL_MOTD, v), _sender);
	}
	_message_user(_generate_reply(RPL_ENDOFMOTD), _sender);
}
