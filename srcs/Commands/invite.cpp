/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:29:56 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 22:38:27 by iwillens         ###   ########.fr       */
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

// Test FT-IRC

// /invite                            > Usage: INVITE <nick> [<channel>], invites someone to a channel, by default the current channel (needs chanop)
//                                        (Message automatic of client, normally server send a ERR_NEEDMOREPARAMS)
// /invite don't_exist                > don't_exist :No such nick
// /invite exist                      > ServerName :No such channel
//                                        (Servername added by client, normally server send a ERR_NEEDMOREPARAMS)
// /invite don't_exist don't_exist    > don't_exist :No such nick
// /invite exist don't_exist          > don't_exist :No such channel
// /invite don't_exist exist          > don't_exist :No such nick
// /invite exist #exist               > #exist :You're not on that channel (Case sender is not on channel)
// /invite exist #exist               > You have been invited to #lop by jean (irc.42network.com) (Case send is chanop)
// /invite exist #exist               > #exist :You're not on that channel (Case send is not chanop)

// Test Undernet

// /invite                            > Usage: INVITE <nick> [<channel>], invites someone to a channel, by default the current channel (needs chanop)
//                                        (Message automatic of client, normally server send a ERR_NEEDMOREPARAMS)
// /invite don't_exist                > don't_exist :No such nick
// /invite exist                      > ServerName :No such channel
//                                        (Servername added by client, normally server send a ERR_NEEDMOREPARAMS)
// /invite don't_exist don't_exist    > don't_exist :No such nick
// /invite exist don't_exist          > don't_exist :No such channel
// /invite don't_exist exist          > don't_exist :No such nick
// /invite exist #exist               > #exist :You're not on that channel (Case sender is not on channel) You've invited roman to #lop (irc.42.ft)
// /invite exist #exist               > You've invited roman to #exist (irc.42.ft) (Case send is chanop)
// /invite exist #exist               > #exist :You're not on that channel (Case send is not chanop)

void	Commands::_cmd_invite(void)
{
	Client     *client = NULL;
	Channel    *channel = NULL;
	std::map<std::string, std::string> m;

	if (_message.arguments().size() >= 1)
		client =  _get_client_by_nickname(_message.arguments(0));
	if (_message.arguments().size() >= 2)
		channel =  _get_channel_by_name(_message.arguments(1));
	else if (_message.arguments().size() <= 0)
	{
		_message_user(_generate_reply(ERR_NEEDMOREPARAMS, "command", _message.command()), _sender);
		return ;
	}
	if (client == NULL)
	{
		_message_user(_generate_reply(ERR_NOSUCHNICK, "nickname", _message.arguments(0)), _sender);
		return ;
	}
	if (channel == NULL)
	{
		_message_user(_generate_reply(ERR_NOSUCHCHANNEL, "channel name", _message.arguments(1)), _sender);
		return ;
	}
	m["nick"] = client->nickname;
	m["channel"] = channel->get_name();
	if (channel->is_user(*_sender) == false)
		_message_user(_generate_reply(ERR_NOTONCHANNEL, "channel", channel->get_name()), _sender);
	else if (channel->is_operator(*_sender) == false)
		_message_user(_generate_reply(ERR_CHANOPRIVSNEEDED, "channel", channel->get_name()), _sender);
	else if (channel->is_user(*client) == true)
		_message_user(_generate_reply(ERR_USERONCHANNEL, m), _sender);
	else
	{
		channel->add_invitation(*client);
		_message_user(_generate_reply(RPL_INVITING, m), _sender);
		std::string msg = _sender->get_prefix() + " INVITE " + client->nickname + " " + channel->get_name() + MSG_ENDLINE;
		_message_user(msg, client);
		if (client->is_away())
		{
			m["away message"] = client->away_message;
			_message_user(_generate_reply(RPL_AWAY, m), _sender);
		}
	}
}
