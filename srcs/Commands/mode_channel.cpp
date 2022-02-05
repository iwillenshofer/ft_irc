/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_channel.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:55:52 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/04 22:58:12 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**   Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]
**               [<ban mask>]
**
**   The MODE command is provided so that channel operators may change the
**   characteristics of `their' channel.  It is also required that servers
**   be able to change channel modes so that channel operators may be
**   created.
**
**   The various modes available for channels are as follows:
**
**           b - set a ban mask to keep users out;
**           i - invite-only channel flag;
**           l - set the user limit to channel;
**           m - moderated channel;
**           n - no messages to channel from clients on the outside;
**           o - give/take channel operator privileges;
**           p - private channel flag;
**           s - secret channel flag;
**           t - topic settable by channel operator only flag;
**           v - give/take the ability to speak on a moderated channel;
**           k - set a channel key (password).
**
**   When using the 'o' and 'b' options, a restriction on a total of three
**   per mode command has been imposed.  That is, any combination of 'o'
**   and
*/

void	Commands::__perform_mode_ban(Channel *channel, char prefix, std::string argument)
{
	std::string msg;
	std::string bans;
	std::vector<std::string> ban_list = channel->get_ban_list();
	std::map<std::string, std::string> m;

	m["channel"] = channel->get_name();
	if (!(argument.size()))
	{
		if (channel->is_user(_sender->nickname) || (!(channel->is_secret()) && !(channel->is_private())))
		{
			for (std::vector<std::string>::iterator it = ban_list.begin(); it != ban_list.end(); it++)
			{
				m["banmask"] = *it;
				_message_user(_generate_reply(RPL_BANLIST, m), _sender);
			}
		}
		_message_user(_generate_reply(RPL_ENDOFBANLIST, m), _sender);
		return ;
	}
	argument = Mask::create(argument);
	if (!(channel->is_operator(_sender->nickname)))
	{
		_message_user(_generate_reply(ERR_CHANOPRIVSNEEDED, m), _sender);
		return;
	}
	try
	{
		if (prefix == '+')
		{
			if (channel->is_banned(argument))
				return ;
			for (std::vector<std::string>::iterator it = ban_list.begin(); it != ban_list.end(); it++)	
			{
				if (Mask::match(*it, argument))
				{
					std::string val = *it;
					channel->remove_ban(_sender->nickname, *it);
					msg = _sender->get_prefix() + " MODE " + channel->get_name() + " -b " + *it + MSG_ENDLINE;
					_message_channel(msg, channel->get_name(), true);
				}
			}
			Debug("Adding Ban: '" + argument + "'");
			channel->add_ban(_sender->nickname, argument);
			msg = _sender->get_prefix() + " MODE " + channel->get_name() + " +b " + argument + MSG_ENDLINE;
			_message_channel(msg, channel->get_name(), true);
		}	
		else
		{
			for (std::vector<std::string>::iterator it = ban_list.begin(); it != ban_list.end(); it++)	
			{
				Debug("Removing: '" + *it + "' | '" + argument + "'");
				if (Mask::match(*it, argument))
				{
					channel->remove_ban(_sender->nickname, *it);
					msg = _sender->get_prefix() + " MODE " + channel->get_name() + " -b " + *it + MSG_ENDLINE;
					_message_channel(msg, channel->get_name(), true);
				}
			}
		}
	}
	catch(int code_error)
	{
		_message_user(_generate_reply(code_error), _sender);
	}
}

void	Commands::__perform_mode_channel(Channel *channel, char mode, char prefix, std::string argument)
{
	std::string msg;

	if (mode == 'b')
	{
		__perform_mode_ban(channel, prefix, argument);
		return ;
	}
	try
	{
		if (prefix == '+')
			channel->activate_mode(_sender->nickname, mode, argument);
		else
			channel->deactivate_mode(_sender->nickname, mode, argument);
		if (argument.size())
			argument = " " + argument;
		msg = _sender->get_prefix() + " MODE " + channel->get_name() + " " + prefix + mode + argument + MSG_ENDLINE;
		_message_channel(msg, channel->get_name(), true);
	}
	catch(int code_error)
	{
		_message_user(_generate_reply(code_error), _sender);
	}
}

void	Commands::_cmd_mode_channel(void)
{
	Channel     *chan;
	char        prefix = '+';
	std::string mode_channel = MODE_CHANNEL;
	std::map<std::string, std::string> m;
	
	if (_message.arguments().size() == 0)
	{
		_message_user(_generate_reply(ERR_NEEDMOREPARAMS), _sender);
		return ;
	}
	chan =  _get_channel_by_name(_message.arguments(0));
	if (chan == NULL)
	{
		_message_user(_generate_reply(ERR_NOSUCHCHANNEL), _sender);
		return ;
	}  
	if (chan->is_user(_sender->nickname) == false)
	{
		_message_user(_generate_reply(ERR_NOTONCHANNEL), _sender);
		return ;
	}
	if (_message.arguments().size() == 1)
	{
		m["channel"] = chan->get_name();
		m["mode"] = chan->get_modes();
		m["mode_params"] = chan->get_mode_params();
		_message_user(_generate_reply(RPL_CHANNELMODEIS, m), _sender);
		return ;
	}
	for (std::string::iterator it = _message.arguments(1).begin(); it != _message.arguments(1).end(); it ++)
	{
		if (mode_channel.find(*it) == std::string::npos)
			_message_user(_generate_reply(ERR_UNKNOWNMODE), _sender);
		else if (*it == '+' || *it == '-')
			prefix = *it;
		else if (_message.arguments().size() > 2)
			__perform_mode_channel(chan, *it, prefix, _message.arguments(2));
		else
			__perform_mode_channel(chan, *it, prefix);
	}
}
