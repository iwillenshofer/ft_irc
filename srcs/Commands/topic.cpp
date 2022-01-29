/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:13 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/29 11:55:07 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.2.4 Topic message
**	Command: TOPIC
**	Parameters: <channel> [ <topic> ]
**	
**	The TOPIC command is used to change or view the topic of a channel.
**	The topic for channel <channel> is returned if there is no <topic>
**	given.  If the <topic> parameter is present, the topic for that
**	channel will be changed, if this action is allowed for the user
**	requesting it.  If the <topic> parameter is an empty string, the
**	topic for that channel will be removed.
**	
**	Numeric Replies:
**	
**			ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
**			RPL_NOTOPIC                     RPL_TOPIC
**			ERR_CHANOPRIVSNEEDED            ERR_NOCHANMODES
**	
**	Examples:
**	
**	:WiZ!jto@tolsun.oulu.fi TOPIC #test :New topic ; User Wiz setting the
**									topic.
**	
**	TOPIC #test :another topic      ; Command to set the topic on #test
**									to "another topic".
**	
**	TOPIC #test :                   ; Command to clear the topic on
**									#test.
**	
**	TOPIC #test                     ; Command to check the topic for
**									#test.
*/

void	Commands::__perform_topic(Channel *channel, std::map<std::string, std::string> &args, bool broadcast)
{
		args["channel"] = channel->get_name();
		args["topic"] = channel->get_topic();
		if (!broadcast)
		{
			if (channel->get_topic() == "")
				_message_user(_generate_reply(RPL_NOTOPIC, args), _sender);
			else
				_message_user(_generate_reply(RPL_TOPIC, args), _sender);
		}
		else
		{
			_message_channel(_sender->get_prefix() + " TOPIC " + channel->get_name() + " :" + channel->get_topic() + MSG_ENDLINE, channel->get_name(), true);
		}
}


void	Commands::_cmd_topic(void)
{
	Channel *channel;
	std::string topic;
	std::map<std::string, std::string> m;

	if (!_message.arguments().size())
	{
		_message_user(_generate_reply(ERR_NEEDMOREPARAMS), _sender);
		return ;
	}
	channel = _get_channel_by_name(_message.arguments()[0]);
	if (!(channel) || !(channel->is_user(_sender->nickname)))
		_message_user(_generate_reply(ERR_NOTONCHANNEL), _sender);
	else if (_message.arguments().size() == 1)
		__perform_topic(channel, m, false);
	else
	{
		topic = _message.arguments()[1];
		if (topic.size() >= 2 && ((topic[0] == '\'' && topic[topic.size() - 1] == '\'') || (topic[0] == '\"' && topic[topic.size() - 1] == '\"')))
		{
			topic.erase(0, 1);
			topic.erase(topic.size() - 1);
		}
		try
		{
			channel->set_topic(_sender->nickname, topic);
			__perform_topic(channel, m, true);
		}
		catch(int error_code)
		{
			m["channel"] = channel->get_name();
			_message_user(_generate_reply(error_code, m), _sender);
		}
	}
}
