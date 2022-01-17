/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:14 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:29:47 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.4.1 Motd message
**	Command: MOTD
**	Parameters: [ <target> ]
**	
**	The MOTD command is used to get the "Message Of The Day" of the given
**	server, or current server if <target> is omitted.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**			RPL_MOTDSTART                   RPL_MOTD
**			RPL_ENDOFMOTD                   ERR_NOMOTD
*/

void	Commands::_cmd_motd(void)
{
	_message_user(_generate_reply(RPL_MOTDSTART), _sender);
	_message_user(_generate_reply(RPL_MOTD), _sender);
	_message_user(_generate_reply(RPL_ENDOFMOTD), _sender);
}
