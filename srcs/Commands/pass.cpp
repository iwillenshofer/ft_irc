/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:50 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/08 21:59:26 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.1.1 Password message
**	Command: PASS
**	Parameters: <password>
**	
**	The PASS command is used to set a 'connection password'.  The
**	optional password can and MUST be set before any attempt to register
**	the connection is made.  Currently this requires that user send a
**	PASS command before sending the NICK/USER combination.
**	
**	Numeric Replies:
**			ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
**	
**	Example:
**			PASS secretpasswordhere
*/

void	Commands::_cmd_pass(void)
{
	if (_sender->registered)
		_message_user(_generate_reply(ERR_ALREADYREGISTRED), _sender);
	else if (!(_message.arguments().size()))
		_message_user(_generate_reply(ERR_NEEDMOREPARAMS), _sender);
    else
    {
        _sender->password = ft::hash(_message.arguments(0).c_str());
    }
}
