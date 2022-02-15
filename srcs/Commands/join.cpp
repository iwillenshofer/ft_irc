/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:29:58 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 22:08:13 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.2.1 Join message
**	Command: JOIN
**	Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] ) / "0"
**	
**	The JOIN command is used by a user to request to start listening to
**	the specific channel.  Servers MUST be able to parse arguments in the
**	form of a list of target, but SHOULD NOT use lists when sending JOIN
**	messages to clients.
**	
**	Once a user has joined a channel, he receives information about
**	all commands his server receives affecting the channel.  This
**	includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
**	This allows channel members to keep track of the other channel
**	members, as well as channel modes.
**	
**	If a JOIN is successful, the user receives a JOIN message as
**	confirmation and is then sent the channel's topic (using RPL_TOPIC) and
**	the list of users who are on the channel (using RPL_NAMREPLY), which
**	MUST include the user joining.
**	
**	Note that this message accepts a special argument ("0"), which is
**	a special request to leave all channels the user is currently a member
**	of.  The server will process this message as if the user had sent
**	a PART command (See Section 3.2.2) for each channel he is a member
**	of.
**	
**	Numeric Replies:
**			ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
**			ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
**			ERR_CHANNELISFULL               ERR_BADCHANMASK
**			ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
**			ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
**			RPL_TOPIC
**	
**	Examples:
**	JOIN #foobar                    ; Command to join channel #foobar.
**	
**	JOIN &foo fubar                 ; Command to join channel &foo using
**									key "fubar".
**	
**	JOIN #foo,&bar fubar            ; Command to join channel #foo using
**									key "fubar" and &bar using no key.
**	
**	JOIN #foo,#bar fubar,foobar     ; Command to join channel #foo using
**									key "fubar", and channel #bar using
**									key "foobar".
**	
**	JOIN #foo,#bar                  ; Command to join channels #foo and
**									#bar.
**	
**	JOIN 0                          ; Leave all currently joined
**									channels.
**	
**	:WiZ!jto@tolsun.oulu.fi JOIN #Twilight_zone ; JOIN message from WiZ
**									on channel #Twilight_zone
*/

// < :iwillens2!~iwillens2@177.73.71.99 JOIN #brasil
//< :iwillens2!iwillens2@localhost JOIN #brasil

void	Commands::_cmd_join(void)
{
	Channel *channel;
	std::vector<std::string> u;
	std::vector<std::string> p;
	std::map<std::string, std::string> m;

	_message.print();
	if (!(_message.arguments().size()))
	{
		_message_user(_generate_reply(ERR_NEEDMOREPARAMS), _sender);
		return ;
	}
	if (_message.arguments(0) == "0")
	{
		Debug("ARGUMENT: " + _message.arguments(0), DBG_ERROR);
		for (Commands::channel_iterator it = _channels->begin(); it != _channels->end(); it++)
		{
			if (it->second.is_user(*_sender))
			{
				_message_channel(_sender->get_prefix() + " PART " + it->second.get_name() + " :Leaving" + MSG_ENDLINE, it->second.get_name(), true);
				it->second.remove_user(*_sender);
			}
		}
		return;
	}
	Message::remove_double_commas(_message.arguments(0));
	u = ft::split(_message.arguments(0), ',');
	if (_message.arguments().size() > 1)
	{
		Message::remove_double_commas(_message.arguments(1));
		p = ft::split(_message.arguments(1), ',');
	}
	while (p.size() < u.size())
		p.push_back("");
	for (std::vector<std::string>::iterator it = u.begin(); it != u.end(); it++)
	{
		m["channel name"] = *it;
		if (!(Message::is_bnf_channel(*it)))
			_message_user(_generate_reply(ERR_NOSUCHCHANNEL, m), _sender);
		else if (!(channel = _get_channel_by_name(*it)))
		{
			Channel ch(*it, *_sender);
			channel = &((_channels->insert(std::make_pair(*it, ch)).first)->second);
			_message_channel(_sender->get_prefix() + " JOIN " + *it + MSG_ENDLINE, *it, true);
			__perform_names(*channel);
		}
		else
		{
			if (channel->is_user(*_sender))
				continue ;
			try
			{
				channel->add_user(*_sender, ft::hash(p[it - u.begin()].c_str()));
				_message_channel(_sender->get_prefix() + " JOIN " + *it + MSG_ENDLINE, *it, true);
				__perform_names(*channel);
			}
			catch(int code_error)
			{
                _message_user(_generate_reply(code_error), _sender);
			}
		}
	}
}
