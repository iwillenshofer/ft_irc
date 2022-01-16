/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:11 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:30:21 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.4.6 Time message
**	Command: TIME
**	Parameters: [ <target> ]
**	
**	The time command is used to query local time from the specified
**	server. If the <target> parameter is not given, the server receiving
**	the command must reply to the query.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**	
**			ERR_NOSUCHSERVER              RPL_TIME
**	
**	Examples:
**	TIME tolsun.oulu.fi             ; check the time on the server
**									"tolson.oulu.fi"
*/

void	Commands::_cmd_time(void)
{

}
