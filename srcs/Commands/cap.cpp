/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 23:19:09 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/18 23:28:40 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
** the CAP command is added for compatibility, as some clients send it during
** connection to verify server capability. (irc v3)
** https://ircv3.net/specs/extensions/capability-negotiation.html
*/

void Commands::_cmd_cap(void)
{
	return ;
}
