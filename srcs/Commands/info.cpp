/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:29:54 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:29:16 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.4.10 Info command
**	Command: INFO
**	Parameters: [ <target> ]
**	The INFO command is REQUIRED to return information describing the
**	server: its version, when it was compiled, the patchlevel, when it
**	was started, and any other miscellaneous information which may be
**	considered to be relevant.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**			ERR_NOSUCHSERVER
**			RPL_INFO                      RPL_ENDOFINFO
**	
**	Examples:
**	INFO csd.bu.edu                 ; request an INFO reply from
**									csd.bu.edu
**	
**	INFO Angel                      ; request info from the server that
**									Angel is connected to.
*/

void	Commands::_cmd_info(void)
{

}
