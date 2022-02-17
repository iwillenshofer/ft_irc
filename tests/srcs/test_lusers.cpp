/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lusers.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:12 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/16 19:33:01 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_lusers(void)
{
	title("lusers");
	std::string nick;
	IrcClient c[10];

	description("Testing luser command with 10 users");
	for (int i = 0; i < 10; i++)
	{
		nick = "client" + ft::to_string(i);
		c[i] = IrcClient(_host, _port);
		c[i].command("PASS " + _password + "\r\n", false);
		c[i].command("USER " + nick + " 8 * :Client Name\r\n", false);
		c[i].command("NICK " + nick + "\r\n", false);
		c[i].listen(false);
		if (i % 3)
			c[i].command("MODE " + nick + " -i\r\n", false);
		c[i].listen(false);
	}
	c[0].command("LUSERS irc.unknownserver.com\r\n");
	c[0].listen();
	c[0].command("LUSERS irc.42network.com irc.unknownserver.com\r\n");
	c[0].listen();
	c[0].command("LUSERS irc.unknownserver.com irc.42network.com\r\n");
	c[0].listen();
	c[0].command("LUSERS * irc.42network.com\r\n");
	c[0].listen();
	c[0].command("LUSERS\r\n");
	c[0].listen();
	c[0].command("JOIN #channel\r\n");
	c[0].command("JOIN #channel1\r\n");
	c[0].command("OPER iwillens Igor123\r\n");
	c[0].listen(false);
	c[0].command("LUSERS *\r\n");
	c[0].listen();
}
