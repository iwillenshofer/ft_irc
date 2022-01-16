/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:29:56 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 20:29:30 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

/*
**	RFC 2812: https://datatracker.ietf.org/doc/html/rfc2812
**	3.2.7 Invite message
**	Command: INVITE
**	Parameters: <nickname> <channel>
**	
**	The INVITE command is used to invite a user to a channel.  The
**	parameter <nickname> is the nickname of the person to be invited to
**	the target channel <channel>.  There is no requirement that the
**	channel the target user is being invited to must exist or be a valid
**	channel.  However, if the channel exists, only members of the channel
**	are allowed to invite other users.  When the channel has invite-only
**	flag set, only channel operators may issue INVITE command.
**	
**	Only the user inviting and the user being invited will receive
**	notification of the invitation.  Other channel members are not
**	notified.  (This is unlike the MODE changes, and is occasionally the
**	source of trouble for users.)
**	
**	Numeric Replies:
**	
**			ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
**			ERR_NOTONCHANNEL                ERR_USERONCHANNEL
**			ERR_CHANOPRIVSNEEDED
**			RPL_INVITING                    RPL_AWAY
**	
**	Examples:
**	
**	:Angel!wings@irc.org INVITE Wiz #Dust
**	
**									; Message to WiZ when he has been
**									invited by user Angel to channel
**									#Dust
**	
**	INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
**									#Twilight_zone
*/

void	Commands::_cmd_invite(void)
{

}
