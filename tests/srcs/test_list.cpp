/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:09 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/16 23:03:22 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_list(void)
{
	IrcClient c[10];
	std::string nick;

	title("list");
	description("Testing list, before and after joining a channel, being client2 visible,"
				"and #channel1 secret.");
	for (int i = 0; i < 4; i++)
	{
		nick = "client" + ft::to_string(i);
		c[i] = IrcClient(_host, _port);
		c[i].command("PASS " + _password + "\r\n", false);
		c[i].command("USER " + nick + " 8 * :Client Name\r\n", false);
		c[i].command("NICK " + nick + "\r\n", false);
		c[i].listen(false);
		if (i)
		{
			for (int j = 0; j < 4; j++)
			{
				c[i].command("JOIN #channel" + ft::to_string(j) + "\r\n", false);
				if (i == 1)
					c[i].command("TOPIC #channel" + ft::to_string(j) + " :This is channel " + ft::to_string(j) + "\r\n",false);
			}
			c[i].listen(false);
		}
	}
	c[2].command("MODE client2 -i\r\n", false);
	c[2].listen(false);
	c[1].command("MODE #channel1 +s \r\n",false);
	c[1].listen(false);
	c[0].command("LIST #channel1 unknown_server\r\n");
	c[0].listen();
	c[0].command("LIST #channel1 irc.42network.com\r\n");
	c[0].listen();
	c[0].command("LIST #channel1,#channel2,#channel3 irc.42network.com\r\n");
	c[0].listen();
	c[0].command("LIST\r\n");
	c[0].listen();
	for (int i = 1; i < 4; i++)
		c[0].command("JOIN #channel" + ft::to_string(i) + "\r\n", false);
	c[0].listen(false);
	c[0].command("LIST\r\n");
	c[0].listen();

}
