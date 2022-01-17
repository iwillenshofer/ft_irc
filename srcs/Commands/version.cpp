/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:31:19 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:30:27 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.4.3 Version message
**	Command: VERSION
**	Parameters: [ <target> ]
**	
**	The VERSION command is used to query the version of the server
**	program.  An optional parameter <target> is used to query the version
**	of the server program which a client is not directly connected to.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**			ERR_NOSUCHSERVER                RPL_VERSION
**	
**	Examples:
**	VERSION tolsun.oulu.fi          ; Command to check the version of
**									server "tolsun.oulu.fi".
*/

void	Commands::_cmd_version(void)
{

}
