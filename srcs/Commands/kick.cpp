/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:00 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/16 21:00:45 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.2.8 Kick command
**	Command: KICK
**	Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
**				[<comment>]
**	
**	The KICK command can be used to request the forced removal of a user
**	from a channel.  It causes the <user> to PART from the <channel> by
**	force.  For the message to be syntactically correct, there MUST be
**	either one channel parameter and multiple user parameter, or as many
**	channel parameters as there are user parameters.  If a "comment" is
**	given, this will be sent instead of the default message, the nickname
**	of the user issuing the KICK.
**	
**	The server MUST NOT send KICK messages with multiple channels or
**	users to clients.  This is necessarily to maintain backward
**	compatibility with old client software.
**	
**	Numeric Replies:
**			ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
**			ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
**			ERR_USERNOTINCHANNEL            ERR_NOTONCHANNEL
**	
**	Examples:
**	KICK &Melbourne Matthew         ; Command to kick Matthew from
**									&Melbourne
**	
**	KICK #Finnish John :Speaking English
**									; Command to kick John from #Finnish
**									using "Speaking English" as the
**									reason (comment).
**	
**	:WiZ!jto@tolsun.oulu.fi KICK #Finnish John
**									; KICK message on channel #Finnish
**									from WiZ to remove John from channel
*/

void	Commands::_cmd_kick(void)
{
	std::map<std::string, std::string> m;
	std::vector<std::string> channels;
	std::vector<std::string> users;
	Channel *channel;
	Client *client;
	std::string reason;

	m["command"] = _message.command();
	if ((_message.arguments().size()) < 2)
		_message_user(_generate_reply(ERR_NEEDMOREPARAMS, m), _sender);
	else
	{
		reason = (_message.arguments().size() > 2) ? _message.arguments(2) : std::string(SRV_DFLKICKMSG);
		channels = Message::split_commas(_message.arguments(0), true);
		users = Message::split_commas(_message.arguments(1), true);
		for (std::vector<std::string>::iterator cit = channels.begin(); cit != channels.end(); cit++)
		{
			m["channel name"] = *cit;
			m["channel"] = *cit;
			channel = _get_channel_by_name(*cit);
			if (!(Message::is_bnf_channel(*cit)))
				_message_user(_generate_reply(ERR_BADCHANMASK, m), _sender);
			else if (!(channel))
				_message_user(_generate_reply(ERR_NOSUCHCHANNEL, m), _sender);
			else if (!(channel->is_user(*_sender)))
				_message_user(_generate_reply(ERR_NOTONCHANNEL, m), _sender);
			else if (!(channel->is_operator(*_sender)))
				_message_user(_generate_reply(ERR_CHANOPRIVSNEEDED, m), _sender);
			else
			{
				for (std::vector<std::string>::iterator uit = users.begin(); uit != users.end(); uit++)
				{
					m["nick"] = *uit;
					client = _get_client_by_nickname(*uit);
					if (!(client) || !(channel->is_user(*client)))
						_message_user(_generate_reply(ERR_USERNOTINCHANNEL, m), _sender);
					else
					{
						_message_channel(_sender->get_prefix() + " KICK " + channel->get_name() + " " + *uit + " :" + reason + MSG_ENDLINE, channel->get_name(), true);
						channel->remove_user(*client);
					}
				}
				if (channel->is_empty())
					_channels->erase(channel->get_name());
			}
		}
	}
}
