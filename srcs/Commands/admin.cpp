/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:29:44 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/17 22:43:55 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.4.9 Admin command
**	Command: ADMIN
**	Parameters: [ <target> ]
**	
**	The admin command is used to find information about the administrator
**	of the given server, or current server if <target> parameter is
**	omitted.  Each server MUST have the ability to forward ADMIN messages
**	to other servers.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**			ERR_NOSUCHSERVER
**			RPL_ADMINME                   RPL_ADMINLOC1
**			RPL_ADMINLOC2                 RPL_ADMINEMAIL
**	
**	Examples:
**	ADMIN tolsun.oulu.fi            ; request an ADMIN reply from
**									tolsun.oulu.fi
**	
**	ADMIN syrk                      ; ADMIN request for the server to
**									which the user syrk is connected
*/

void	Commands::_cmd_admin(void)
{
    bool    match = true;
    
    if (_message.arguments().empty() == false)
    {
        match = Mask::match_raw(_server->servername(), _message.arguments(0));
        if (match == false && _sender->is_operator() == false)
        {
            _message_user(_generate_reply(ERR_NOPRIVILEGES, "", ""), _sender);
            return ;
        }
    }
    if (match == true)
    {
        _message_user(_generate_reply(RPL_ADMINME, "server", SRV_SERVERNAME), _sender);
        _message_user(_generate_reply(RPL_ADMINLOC1, "info1",MSG_NAME_SERVER), _sender);
        _message_user(_generate_reply(RPL_ADMINLOC2, "info2", ""), _sender);
        _message_user(_generate_reply(RPL_ADMINEMAIL, "email", MSG_ADMIN1), _sender);
        _message_user(_generate_reply(RPL_ADMINEMAIL, "email", MSG_ADMIN2), _sender);
    }
    else
        _message_user(_generate_reply(ERR_NOSUCHSERVER, "server name", _message.arguments(0)), _sender);
}
