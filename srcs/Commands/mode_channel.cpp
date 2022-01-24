/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:55:52 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/23 21:28:00 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.2.3 Channel mode message
**	Command: MODE
**	Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )
**	
**	The MODE command is provided so that users may query and change the
**	characteristics of a channel.  For more details on available modes
**	and their uses, see "Internet Relay Chat: Channel Management" [IRC-
**	CHAN].  Note that there is a maximum limit of three (3) changes per
**	command for modes that take a parameter.
**	
**	Numeric Replies:
**			ERR_NEEDMOREPARAMS              ERR_KEYSET
**			ERR_NOCHANMODES                 ERR_CHANOPRIVSNEEDED
**			ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
**			RPL_CHANNELMODEIS
**			RPL_BANLIST                     RPL_ENDOFBANLIST
**			RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
**			RPL_INVITELIST                  RPL_ENDOFINVITELIST
**			RPL_UNIQOPIS
**	
**	The following examples are given to help understanding the syntax of
**	the MODE command, but refer to modes defined in "Internet Relay Chat:
**	Channel Management" [IRC-CHAN].
**	
**	Examples:
**	MODE #Finnish +imI *!*@*.fi     ; Command to make #Finnish channel
**									moderated and 'invite-only' with user
**									with a hostname matching *.fi
**									automatically invited.
**	
**	MODE #Finnish +o Kilroy         ; Command to give 'chanop' privileges
**									to Kilroy on channel #Finnish.
**	
**	MODE #Finnish +v Wiz            ; Command to allow WiZ to speak on
**									#Finnish.
**	
**	MODE #Fins -s                   ; Command to remove 'secret' flag
**									from channel #Fins.
**	
**	MODE #42 +k oulu                ; Command to set the channel key to
**									"oulu".
**	
**	MODE #42 -k oulu                ; Command to remove the "oulu"
**									channel key on channel "#42".
**	
**	MODE #eu-opers +l 10            ; Command to set the limit for the
**									number of users on channel
**									"#eu-opers" to 10.
**	
**	:WiZ!jto@tolsun.oulu.fi MODE #eu-opers -l
**									; User "WiZ" removing the limit for
**									the number of users on channel "#eu-
**									opers".
**	
**	MODE &oulu +b                   ; Command to list ban masks set for
**									the channel "&oulu".
**	
**	MODE &oulu +b *!*@*             ; Command to prevent all users from
**									joining.
**	
**	MODE &oulu +b *!*@*.edu +e *!*@*.bu.edu
**									; Command to prevent any user from a
**									hostname matching *.edu from joining,
**									except if matching *.bu.edu
**	
**	MODE #bu +be *!*@*.edu *!*@*.bu.edu
**									; Comment to prevent any user from a
**									hostname matching *.edu from joining,
**									except if matching *.bu.edu
**	
**	MODE #meditation e              ; Command to list exception masks set
**									for the channel "#meditation".
**	
**	MODE #meditation I              ; Command to list invitations masks
**									set for the channel "#meditation".
**	
**	MODE !12345ircd O               ; Command to ask who the channel
**									creator for "!12345ircd" is
*/

void	Commands::_cmd_mode_channel(void)
{
    Channel     *chan =  _get_channel_by_name(_message.arguments()[0]);
    std::string mode_channel = MODE_CHANNEL;
    char        prefix = '+';
    bool        is_arg;
    
    try
    {
        _message.arguments().at(2);
        is_arg = true;
    }
    catch(const std::exception& e)
    {
        is_arg = false;
    } 
    if (chan == NULL)
    {
        _message_user(_generate_reply(ERR_NOSUCHCHANNEL), _sender);
        return ;
    }  
    else if (chan->is_user(_sender->nickname) == false)
    {
        _message_user(_generate_reply(ERR_NOTONCHANNEL), _sender);
        return ;
    }     
    for (size_t i = 0; i < _message.arguments()[1].size(); i++)
    {
        if (mode_channel.find(_message.arguments()[1].at(i)) == std::string::npos)
        {
            _message_user(_generate_reply(ERR_UNKNOWNMODE), _sender);
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
                if (is_arg == true)
                    chan->activate_mode(_sender->nickname, _message.arguments()[1].at(i), _message.arguments()[2]);
                else
                    chan->activate_mode(_sender->nickname, _message.arguments()[1].at(i));
            }
            catch(const std::exception& e)
            {
                Debug("To implement to return the good message to client");
            }
        }
        else
        {
            try
            {
                if (is_arg == true)
                    chan->desactivate_mode(_sender->nickname, _message.arguments()[1].at(i), _message.arguments()[2]);
                else
                    chan->desactivate_mode(_sender->nickname, _message.arguments()[1].at(i));
            }
            catch(const std::exception& e)
            {
                Debug("To implement to return the good message to client");
            }
        }
    }
}
