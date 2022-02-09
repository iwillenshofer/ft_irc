/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:29:56 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/08 20:03:12 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.2.7 Invite message
**	Command: INVITE
**	Parameters: <nickname> <channel>
**	
**	The INVITE command is used to invite a user to a channel.  The
**	parameter <nickname> is the nickname of the person to be invited to
**	the target channel <channel>.  There is no requirement that the
**	channel the target user is being invited to must exist or be a valid
**	channel.  However, if the channel exists, only members of the channel
**	are allowed to invite other users.  When the channel has invite-only
**	flag set, only channel operators may issue INVITE command.
**	
**	Only the user inviting and the user being invited will receive
**	notification of the invitation.  Other channel members are not
**	notified.  (This is unlike the MODE changes, and is occasionally the
**	source of trouble for users.)
**	
**	Numeric Replies:
**	
**			ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
**			ERR_NOTONCHANNEL                ERR_USERONCHANNEL
**			ERR_CHANOPRIVSNEEDED
**			RPL_INVITING                    RPL_AWAY
**	
**	Examples:
**	
**	:Angel!wings@irc.org INVITE Wiz #Dust
**	
**									; Message to WiZ when he has been
**									invited by user Angel to channel
**									#Dust
**	
**	INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
**									#Twilight_zone
*/

void	Commands::_cmd_invite(void)
{
    Client     *client;
    Channel    *channel;
    std::map<std::string, std::string> m;

    if (_message.arguments().size() != 2)
    {
        m["command"] = "invite";
        _message_user(_generate_reply(ERR_NEEDMOREPARAMS, m), _sender);
        return ;
    }
	client =  _get_client_by_nickname(_message.arguments(0));
    channel =  _get_channel_by_name(_message.arguments(1));
    if (client == NULL)
    {
        m["nickname"] = _message.arguments(0);
        _message_user(_generate_reply(ERR_NOSUCHNICK, m), _sender);
        return ;
    }
    if (channel == NULL)
    {
        m["channel name"] = _message.arguments(1);
        _message_user(_generate_reply(ERR_NOSUCHCHANNEL, m), _sender);
        return ;
    }
    m["nick"] = client->nickname;
    m["channel"] = channel->get_name();
    if (channel->is_user(*_sender) == false)
    {
        _message_user(_generate_reply(ERR_NOTONCHANNEL, m), _sender);
        return ;
    }
    if (channel->is_invitation_only() == true && channel->is_operator(*_sender) == false)
    {
        _message_user(_generate_reply(ERR_CHANOPRIVSNEEDED, m), _sender);
        return ;
    }
    if (channel->is_user(*client) == true)
    {
        _message_user(_generate_reply(ERR_USERONCHANNEL, m), _sender);
        return ;
    }
    channel->add_invitation(*client);
    _message_user(_generate_reply(RPL_INVITING, m), _sender);
    std::string msg = _sender->get_prefix() + " INVITE " + client->nickname + " " + channel->get_name() + MSG_ENDLINE;
    _message_user(msg, client);
    //if (client->is_away() == true)
    //{
    //    _message_user(_generate_reply(RPL_AWAY), _sender);
    //}
}
