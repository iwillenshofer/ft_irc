/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_user.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 19:58:45 by roman             #+#    #+#             */
/*   Updated: 2022/01/28 21:25:48 by iwillens         ###   ########.fr       */
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
	Debug("Message Size: " + ft::to_string(_message.arguments()[1].size()), DBG_ERROR);
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
				Debug("PREFIX +", DBG_ERROR);
                std::string msg;
                client->activate_mode(_message.arguments()[1].at(i));
                msg = _sender->get_prefix() + " MODE " + _message.arguments()[0] + " +" + _message.arguments()[1].at(i) + MSG_ENDLINE;
	            //_message_channel(msg, _message.arguments()[0], true);
				_message_user(msg, _sender);
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
				Debug("PREFIX -: ", DBG_ERROR);
                std::string msg;
                client->deactivate_mode(_message.arguments()[1].at(i));
                msg = _sender->get_prefix() + " MODE " + _message.arguments()[0] + " -" + _message.arguments()[1].at(i) + MSG_ENDLINE;
//	            _message_channel(msg, _message.arguments()[0], true);
                _message_user(msg, _sender);

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
