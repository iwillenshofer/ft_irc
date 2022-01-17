/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:30:46 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:30:03 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.1.4 Oper message
**	Command: OPER
**	Parameters: <name> <password>
**	
**	A normal user uses the OPER command to obtain operator privileges.
**	The combination of <name> and <password> are REQUIRED to gain
**	Operator privileges.  Upon success, the user will receive a MODE
**	message (see section 3.1.5) indicating the new user modes.
**	
**	Numeric Replies:
**			ERR_NEEDMOREPARAMS              RPL_YOUREOPER
**			ERR_NOOPERHOST                  ERR_PASSWDMISMATCH
**	
**	Example:
**	OPER foo bar                    ; Attempt to register as an operator
**									using a username of "foo" and "bar"
**									as the password.
*/

void	Commands::_cmd_oper(void)
{

}
