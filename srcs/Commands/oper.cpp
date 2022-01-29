/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:46 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/29 09:57:56 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.1.4 Oper message
**	Command: OPER
**	Parameters: <name> <password>
**	
**	A normal user uses the OPER command to obtain operator privileges.
**	The combination of <name> and <password> are REQUIRED to gain
**	Operator privileges.  Upon success, the user will receive a MODE
**	message (see section 3.1.5) indicating the new user modes.
**	
**	Numeric Replies:
**			ERR_NEEDMOREPARAMS              RPL_YOUREOPER
**			ERR_NOOPERHOST                  ERR_PASSWDMISMATCH
**	
**	Example:
**	OPER foo bar                    ; Attempt to register as an operator
**									using a username of "foo" and "bar"
**									as the password.
*/

void	Commands::_cmd_oper(void)
{
    std::map<std::string, std::string>::iterator it;
    std::string flags = " :+";

    if (_message.arguments().size() != 2)
    {
        _message_user(_generate_reply(ERR_NEEDMOREPARAMS), _sender);
        return ;
    }
    it = _server->operators().find(_message.arguments()[0]);
    if (it == _server->operators().end())
    {
        _message_user(_generate_reply(ERR_NOOPERHOST), _sender);
        return ;
    }
    if (_message.arguments()[1] != it->second)
    {
        _message_user(_generate_reply(ERR_PASSWDMISMATCH), _sender);
        return ;
    }
    try
    {   _sender->set_operator();
        flags += "o";
        _sender->set_receive_notices();
        flags += "s";
    }
    catch(int code)
    {
        if (code == -1)
            code = -1; //Do nothing just continue
    }
    if (flags != " :+")
    {
        std::string msg = _sender->get_prefix() + " MODE " + _sender->nickname + flags + MSG_ENDLINE;
	    _message_user(msg, _sender);
    }
    _message_user(_generate_reply(RPL_YOUREOPER), _sender);
    // TODO :NOTICE ALL USER THAT I AM THE BOSS
}
