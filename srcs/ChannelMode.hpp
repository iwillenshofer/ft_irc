/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMode.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 21:22:26 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 21:29:15 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELMODE_HPP
# define CHANNELMODE_HPP

/*
** Channel modes.
** O; give "channel creator" status; *
** o; give/take channel operator privilege;
** v; give/take the voice privilege;
** a; toggle the anonymous channel flag; *
** i; toggle the invite-only channel flag;
** m; toggle the moderated channel;
** n; toggle the no messages to channel from clients on the outside;
** q; toggle the quiet channel flag;
** p; toggle the private channel flag;
** s; toggle the secret channel flag;
** r; toggle the server reop channel flag;
** t; toggle the topic settable by channel operator only flag;
** k; set/remove the channel key (password);
** l; set/remove the user limit to channel;
** b; set/remove ban mask to keep users out;
** e; set/remove an exception mask to override a ban mask;
** I; set/remove an invitation mask to automatically overridethe invite-only flag;
*/

class ChannelMode
{
	public: 
		ChannelMode(void);
		ChannelMode(ChannelMode const &cp);
		ChannelMode &operator=(ChannelMode const &cp);
		virtual ~ChannelMode();

		bool O;
		bool o;
		bool v;
		bool a;
		bool i;
		bool m;
		bool n;
		bool q;
		bool p;
		bool s;
		bool r;
		bool t;
		bool k;
		bool l;
		bool b;
		bool e;
		bool I;
};

#endif
