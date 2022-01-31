/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:02 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/31 16:27:27 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.7.1 Kill message
**	Command: KILL
**	Parameters: <nickname> <comment>
**	
**	The KILL command is used to cause a client-server connection to be
**	closed by the server which has the actual connection.  Servers
**	generate KILL messages on nickname collisions.  It MAY also be
**	available available to users who have the operator status.
**	
**	Clients which have automatic reconnect algorithms effectively make
**	this command useless since the disconnection is only brief.  It does
**	however break the flow of data and can be used to stop large amounts
**	of 'flooding' from abusive users or accidents.  Abusive users usually
**	don't care as they will reconnect promptly and resume their abusive
**	behaviour.  To prevent this command from being abused, any user may
**	elect to receive KILL messages generated for others to keep an 'eye'
**	on would be trouble spots.
**	
**	In an arena where nicknames are REQUIRED to be globally unique at all
**	times, KILL messages are sent whenever 'duplicates' are detected
**	(that is an attempt to register two users with the same nickname) in
**	the hope that both of them will disappear and only 1 reappear.
**	
**	When a client is removed as the result of a KILL message, the server
**	SHOULD add the nickname to the list of unavailable nicknames in an
**	attempt to avoid clients to reuse this name immediately which is
**	usually the pattern of abusive behaviour often leading to useless
**	"KILL loops".  See the "IRC Server Protocol" document [IRC-SERVER]
**	for more information on this procedure.
**	
**	The comment given MUST reflect the actual reason for the KILL.  For
**	server-generated KILLs it usually is made up of details concerning
**	the origins of the two conflicting nicknames.  For users it is left
**	up to them to provide an adequate reason to satisfy others who see
**	it.  To prevent/discourage fake KILLs from being generated to hide
**	the identify of the KILLer, the comment also shows a 'kill-path'
**	which is updated by each server it passes through, each prepending
**	its name to the path.
**	
**	Numeric Replies:
**	
**			ERR_NOPRIVILEGES              ERR_NEEDMOREPARAMS
**			ERR_NOSUCHNICK                ERR_CANTKILLSERVER
**	
**	NOTE:
**	It is RECOMMENDED that only Operators be allowed to kill other users
**	with KILL command.  This command has been the subject of many
**	controversies over the years, and along with the above
**	recommendation, it is also widely recognized that not even operators
**	should be allowed to kill users on remote servers.
*/

void	Commands::_cmd_kill(void)
{
	std::map<std::string, std::string> m;
	Client *client;


	m["command"] = _message.command();
	m["server"] = _server->servername();
	if ((_message.arguments().size()) < 2)
	{
		_message_user(_generate_reply(ERR_NEEDMOREPARAMS, m), _sender);
		return ;
	}
	else if (_message.arguments(0) == _server->servername())
	{
		_message_user(_generate_reply(ERR_CANTKILLSERVER, m), _sender);
		return ;
	}
	m["nickname"] = _message.arguments(0);
	m["message"] = _message.arguments(1);
	client = _get_client_by_nickname(_message.arguments(0));
	if (!(_sender->is_operator()))
		_message_user(_generate_reply(ERR_NOPRIVILEGES, m), _sender);
	else if (!(client))
		_message_user(_generate_reply(ERR_NOSUCHNICK, m), _sender);
	else
	{
		client->set_hangup(true, Commands::generate_errormsg(ERR_KILLED, m));
		client->get_send_queue().clear();
		_message_user(":" + _server->servername() + " KILL " + _sender->nickname + " :" + _server->servername() + " (" + m["message"] + ")" + MSG_ENDLINE, client);
	}
}
