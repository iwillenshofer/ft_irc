/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:29:54 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/27 20:53:01 by roman            ###   ########.fr       */
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


//>> :irc.42.ft 371 roman :IRC --
//>> :irc.42.ft 371 roman :This program is free software; see LICENSE in the distribution
//>> :irc.42.ft 371 roman :
//>> :irc.42.ft 371 roman :Based on the original code written by Jarkko Oikarinen, version 2.6:
//>> :irc.42.ft 371 roman :Wiz          Jarkko Oikarinen         <jto@tolsun.oulu.fi>
//>> :irc.42.ft 371 roman :
//>> :irc.42.ft 371 roman :The main developer of version u2.9 and u2.10 was:
//>> :irc.42.ft 371 roman :Run          Carlo Wood               <carlo@runaway.xs4all.nl>
//>> :irc.42.ft 371 roman :
//>> :irc.42.ft 371 roman :The head developer of the u2.10 source tree was:
//>> :irc.42.ft 371 roman :Bleep        Thomas Helvey            <tomh@inxpress.net>
//>> :irc.42.ft 371 roman :
//>> :irc.42.ft 371 roman :The current maintainors of the u2.10 source tree are:
//>> :irc.42.ft 371 roman :Isomer       Perry Lorier             <perry@coders.net>
//>> :irc.42.ft 371 roman :Kev          Kevin Mitchell           <klmitch@mit.edu>
//>> :irc.42.ft 371 roman :
//>> :irc.42.ft 371 roman :Contributors to this release:
//>> :irc.42.ft 371 roman :Kev, Isomer, Gte, Ghostwolf, Bleep
//>> :irc.42.ft 371 roman :Debugging and support:
//>> :irc.42.ft 371 roman :SeKs, Maniac-, HeKTik, OmniDynmc, Liandrin, Dianora
//>> :irc.42.ft 371 roman :Special thanks to Angel and Buff for believing in us and puttingup with frantic late night phone calls
//>> :irc.42.ft 371 roman :Thanks goes to all other people who contributed to any version.
//>> :irc.42.ft 371 roman :A full listing of all coders can be found in doc/Authors in the
//>> :irc.42.ft 371 roman :source.
//>> :irc.42.ft 371 roman :
//>> :irc.42.ft 371 roman :Sources:
//>> :irc.42.ft 371 roman :[ IPcheck.c: ddc31e7d362862dab815eb7397e07907  ]
//>> :irc.42.ft 371 roman :[ channel.c: 4e8c1edfe6a3756ec574ddcd15bb6e3c  ]
//>> :irc.42.ft 371 roman :[ class.c: 076ed859560c451a899dd5bb60996145  ]
//>> :irc.42.ft 371 roman :[ client.c: 0e8047cce20d4a2edb38f8bebbe93250  ]
//>> :irc.42.ft 371 roman :Birth Date: Sun Jan 16 2022 at 01:24:49 UTC, compile # 1
//>> :irc.42.ft 371 roman :On-line since Tue Jan 25 21:59:35 2022
//>> :irc.42.ft 374 roman :End of /INFO list.