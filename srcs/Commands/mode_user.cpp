/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_user.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:58:45 by roman             #+#    #+#             */
/*   Updated: 2022/02/17 16:59:10 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**
** 4.2.3.2 User modes
** 
** Parameters: <nickname> {[+|-]|i|w|s|o}
** 
**    The user MODEs are typically changes which affect either how the
**    client is seen by others or what 'extra' messages the client is sent.
**    A user MODE command may only be accepted if both the sender of the
**    message and the nickname given as a parameter are both the same.
** 
**    The available modes are as follows:
** 
**            i - marks a users as invisible;
**            s - marks a user for receipt of server notices;
**            w - user receives wallops;
**            o - operator flag.
** 
**    Additional modes may be available later on.
** 
**    If a user attempts to make themselves an operator using the "+o"
**    flag, the attempt should be ignored.  There is no restriction,
**    however, on anyone `deopping' themselves (using "-o").  Numeric
**    Replies:
** 
**            ERR_NEEDMOREPARAMS             
**            ERR_NOSUCHNICK              
**            ERR_UNKNOWNMODE                 
**            ERR_USERSDONTMATCH              RPL_UMODEIS
**            ERR_UMODEUNKNOWNFLAG
** 
**    Examples:
** :MODE WiZ -w                    ; turns reception of WALLOPS messages
**                                 off for WiZ.
** :Angel MODE Angel +i            ; Message from Angel to make themselves
**                                 invisible.
** MODE WiZ -o                     ; WiZ 'deopping' (removing operator
**                                 status).  The plain reverse of this
**                                 command ("MODE WiZ +o") must not be
**                                 allowed from users since would bypass
**                                 the OPER command.
*/
#include "Commands.hpp"


void	Commands::__perform_mode_user(char mode, char prefix)
{
	std::string msg;

	try
	{
		if (prefix == '+')
			_sender->activate_mode(mode);
		else
			_sender->deactivate_mode(mode);
		msg = _sender->get_prefix() + " MODE " + _sender->nickname + " " + prefix + mode + MSG_ENDLINE;
		_message_user(msg, _sender);
	}
	catch(int code_error)
	{
		if (code_error == -1)
			return ;
		_message_user(_generate_reply(code_error), _sender);
	}
}

void	Commands::_cmd_mode_user(void)
{
    Client     *client =  _get_client_by_nickname(_message.arguments(0));
    std::string mode_user = MODE_USER;
    char        prefix = '+';

    if (client == NULL)
    {
       _message_user(_generate_reply(ERR_NOSUCHNICK, "nickname", _message.arguments(0)), _sender);
       return ;
    }
    else if (_sender != client)
    {
        _message_user(_generate_reply(ERR_USERSDONTMATCH), _sender);
        return ;
    }
    for (size_t i = 0; i < _message.arguments(1).size(); i++)
    {
        if (mode_user.find(_message.arguments(1).at(i)) == std::string::npos)
            _message_user(_generate_reply(ERR_UMODEUNKNOWNFLAG), _sender);
        else if (_message.arguments(1).at(i) == '+' || _message.arguments(1).at(i) == '-')
            prefix = _message.arguments(1).at(i);
        else
			__perform_mode_user(_message.arguments(1).at(i), prefix);
    }
}
