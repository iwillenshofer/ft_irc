/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_user.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:58:45 by roman             #+#    #+#             */
/*   Updated: 2022/01/25 21:35:10 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void	Commands::_cmd_mode_user(void)
{
    Client     *client =  _get_client_by_nickname(_message.arguments()[0]);
    std::string mode_user = MODE_USER;
    char        prefix = '+';

    if (client == NULL)
    {
       _message_user(_generate_reply(ERR_NOSUCHNICK), _sender);
       return ;
    }
    else if (_sender->nickname != client->nickname)
    {
        _message_user(_generate_reply(ERR_USERSDONTMATCH), _sender);
        return ;
    }
    for (size_t i = 0; i < _message.arguments()[1].size(); i++)
    {
        if (mode_user.find(_message.arguments()[1].at(i)) == std::string::npos)
        {
            _message_user(_generate_reply(ERR_UMODEUNKNOWNFLAG), _sender);
            continue;
        }
        if (_message.arguments()[1].at(i) == '+' || _message.arguments()[1].at(i) == '-')
        {
            prefix = _message.arguments()[1].at(i);
            continue;
        }
        if (prefix == '+')
        {
            try
            {
                std::string msg;
                client->activate_mode(_sender->nickname, _message.arguments()[1].at(i));
                msg = _sender->get_prefix() + " MODE " + _message.arguments()[0] + " +" + _message.arguments()[1].at(i) + MSG_ENDLINE;
	            _message_channel(msg, _message.arguments()[0], true);
            }
            catch(int code_error)
            {
                if (code_error == -1)
                    return ;
                _message_user(_generate_reply(code_error), _sender);
            }
        }
        else
        {
            try
            {
                std::string msg;
                client->deactivate_mode(_sender->nickname, _message.arguments()[1].at(i));
                msg = _sender->get_prefix() + " MODE " + _message.arguments()[0] + " -" + _message.arguments()[1].at(i) + MSG_ENDLINE;
	            _message_channel(msg, _message.arguments()[0], true);
            }
            catch(int code_error)
            {
                if (code_error == -1)
                    return ;
                _message_user(_generate_reply(code_error), _sender);
            }
        }
    }


}
