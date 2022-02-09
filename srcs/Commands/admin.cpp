/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:29:44 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/08 20:42:53 by roman            ###   ########.fr       */
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
    std::map<std::string, std::string>  m;
    bool                                match = true;

    if (_message.arguments().empty() == false)
        match = Mask::match_raw(std::string(SRV_SERVERNAME), _message.arguments(0));
    if (match == true)
    {
        m["server"] = SRV_SERVERNAME;
        m["info1"] = MSG_NAME_SERVER;
        m["info2"] = "";
        m["email"] = MSG_ADMIN1;
        _message_user(_generate_reply(RPL_ADMINME, m), _sender);
        _message_user(_generate_reply(RPL_ADMINLOC1, m), _sender);
        _message_user(_generate_reply(RPL_ADMINLOC2, m), _sender);
        _message_user(_generate_reply(RPL_ADMINEMAIL, m), _sender);
        m["email"] = MSG_ADMIN2;
        _message_user(_generate_reply(RPL_ADMINEMAIL, m), _sender);
    }
    else if (_sender->is_operator() == false)
		_message_user(_generate_reply(ERR_NOPRIVILEGES), _sender);
    else
    {
        m["server name"] = _message.arguments(0);
        _message_user(_generate_reply(ERR_NOSUCHSERVER, m), _sender);
    }
}
