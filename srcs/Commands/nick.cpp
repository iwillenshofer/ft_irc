/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:35 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:29:59 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.1.2 Nick message
**	Command: NICK
**	Parameters: <nickname>
**	
**	NICK command is used to give user a nickname or change the existing
**	one.
**	
**	Numeric Replies:
**			ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
**			ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
**			ERR_UNAVAILRESOURCE             ERR_RESTRICTED
**	
**	Examples:
**	NICK Wiz                ; Introducing new nick "Wiz" if session is
**							still unregistered, or user changing his
**							nickname to "Wiz"
**	
**	:WiZ!jto@tolsun.oulu.fi NICK Kilroy
**							; Server telling that WiZ changed his
**							nickname to Kilroy.
*/

void	Commands::_cmd_nick(void)
{
	std::string old_nick = _sender.nickname;
	if (_message.arguments().size() == 0 || _message.arguments()[0].empty())
		_message_user(_generate_reply(ERR_NONICKNAMEGIVEN), _sender);
	else if (_get_client_by_nickname(_message.arguments()[0]) != NULL && _sender.nickname != _message.arguments()[0])
		_message_user(_generate_reply(ERR_NICKNAMEINUSE), _sender);
	else if (!(_validate_nick(_message.arguments()[0])))
		_message_user(_generate_reply(ERR_ERRONEUSNICKNAME), _sender);
	else
	{
		Debug("NICK");
		_sender.nickname = _message.arguments()[0];
		if (_sender.registered)
			_message_user(":" + old_nick + " NICK " + _sender.nickname + "\r\n", _sender); // send message that user changed nickname.
		else if (!(_sender.username.empty()))
			_register_user();
	}
}