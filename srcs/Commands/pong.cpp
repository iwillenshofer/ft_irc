/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:57 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:30:14 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.7.3 Pong message
**	Command: PONG
**	Parameters: <server> [ <server2> ]
**	
**	PONG message is a reply to ping message.  If parameter <server2> is
**	given, this message MUST be forwarded to given target.  The <server>
**	parameter is the name of the entity who has responded to PING message
**	and generated this message.
**	
**	Numeric Replies:
**	
**			ERR_NOORIGIN                  ERR_NOSUCHSERVER
**	
**	Example:
**	
**	PONG csd.bu.edu tolsun.oulu.fi  ; PONG message from csd.bu.edu to
**									tolsun.oulu.fi
**	
*/

void	Commands::_cmd_pong(void)
{
	_sender.is_ping = false;
	_sender.last_ping = time(NULL);
}
