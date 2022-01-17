/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:07 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:29:40 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.2.6 List message
**	Command: LIST
**	Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]
**	
**	The list command is used to list channels and their topics.  If the
**	<channel> parameter is used, only the status of that channel is
**	displayed.
**	
**	If the <target> parameter is specified, the request is forwarded to
**	that server which will generate the reply.
**	
**	Wildcards are allowed in the <target> parameter.
**	
**	Numeric Replies:
**	
**			ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
**			RPL_LIST                        RPL_LISTEND
**	
**	Examples:
**	
**	LIST                            ; Command to list all channels.
**	
**	LIST #twilight_zone,#42         ; Command to list channels
**									#twilight_zone and #42
*/

void	Commands::_cmd_list(void)
{

}
