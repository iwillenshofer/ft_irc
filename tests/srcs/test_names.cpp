/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_names.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:22 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/18 21:03:49 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_names_secret(void)
{
	IrcClient c[5];
	IrcClient cl(_host, _port);
	std::string nick;

	description("Testing MAMES with and without logging into a secret channel, and with all users visible");
	for (int i = 0; i < 5; i++)
	{
		nick = "client" + ft::to_string(i);
		c[i] = IrcClient(_host, _port);
		c[i].command("PASS " + _password + "\r\n", false);
		c[i].command("USER " + nick + " 8 * :Client Name\r\n", false);
		c[i].command("NICK " + nick + "\r\n", false);
		c[i].command("JOIN #channel1\r\n", false);
		c[i].command("MODE " + nick + " -i\r\n", false);
		if (i == 0)
			c[0].command("MODE #channel1 +s\r\n");
		c[i].listen(false);
	}
	cl.command("PASS " + _password + "\r\n", false);
	cl.command("USER client 8 * :Client Name\r\n", false);
	cl.command("NICK client\r\n", false);
	cl.listen(false);
	cl.command("NAMES\r\n");
	cl.listen();
	cl.command("JOIN #channel1\r\n");
	cl.listen(false);
	cl.command("NAMES\r\n");
	cl.listen();
}

void Tester::test_names_invisible(void)
{
	IrcClient c[5];
	IrcClient cl(_host, _port);
	std::string nick;

	description("Testing MAMES with and without logging into a channel, and with all users invisible");
	for (int i = 0; i < 5; i++)
	{
		nick = "client" + ft::to_string(i);
		c[i] = IrcClient(_host, _port);
		c[i].command("PASS " + _password + "\r\n", false);
		c[i].command("USER " + nick + " 8 * :Client Name\r\n", false);
		c[i].command("NICK " + nick + "\r\n", false);
		c[i].command("JOIN #channel1\r\n", false);
		c[i].listen(false);
	}
	cl.command("PASS " + _password + "\r\n", false);
	cl.command("USER client 8 * :Client Name\r\n", false);
	cl.command("NICK client\r\n", false);
	cl.listen(false);
	cl.command("NAMES\r\n");
	cl.listen();
	cl.command("JOIN #channel1\r\n");
	cl.listen(false);
	cl.command("NAMES\r\n");
	cl.listen();
}

void Tester::test_names_visible(void)
{
	IrcClient c[5];
	IrcClient cl(_host, _port);
	std::string nick;

	description("Testing MAMES without logging into a channel, but with all users visible");
	for (int i = 0; i < 5; i++)
	{
		nick = "client" + ft::to_string(i);
		c[i] = IrcClient(_host, _port);
		c[i].command("PASS " + _password + "\r\n", false);
		c[i].command("USER " + nick + " 8 * :Client Name\r\n", false);
		c[i].command("NICK " + nick + "\r\n", false);
		c[i].listen(false);
		c[i].command("JOIN #channel1\r\n", false);
		c[i].command("MODE " + nick + " -i\r\n", false);
		c[i].listen(false);
	}
	cl.command("PASS " + _password + "\r\n", false);
	cl.command("USER client 8 * :Client Name\r\n", false);
	cl.command("NICK client\r\n", false);
	cl.listen(false);
	cl.command("NAMES\r\n");
	cl.listen();
}

void Tester::test_names_general(void)
{
	std::string nick;
	IrcClient c[5];

	description("Testing general applications of NAMES command");
	for (int i = 0; i < 5; i++)
	{
		nick = "client" + ft::to_string(i);
		c[i] = IrcClient(_host, _port);
		c[i].command("PASS " + _password + "\r\n", false);
		c[i].command("USER " + nick + " 8 * :Client Name\r\n", false);
		c[i].command("NICK " + nick + "\r\n", false);
		if (i % 3 || !i)
			c[i].command("JOIN #channel1\r\n", false);
		if (i % 2 || !i)
			c[i].command("JOIN #channel2\r\n", false);
		if (i % 5 || !i)
			c[i].command("JOIN #channel3\r\n", false);
		c[i].listen(false);
	}
	for (int i = 0; i < 5; i++)
		c[i].listen(false);
	c[0].command("NAMES\r\n");
	c[0].listen();
	c[1].command("NAMES #channel1\r\n");
	c[1].listen();
	c[2].command("NAMES #channel1,#channel2\r\n");
	c[2].listen();
	c[2].command("NAMES irc.42network.com\r\n");
	c[2].listen();
	c[2].command("NAMES #channel1,#channel2\r\n");
	c[2].listen();
	c[2].command("NAMES #channel1,#channel2 irc.42network.com\r\n");
	c[2].listen();
	c[2].command("NAMES #channel1,#channel2 unknown_server\r\n");
	c[2].listen();
}

void Tester::test_names(void)
{
	title("names");
	test_names_secret();
	test_names_visible();
	test_names_invisible();
	test_names_general();
	return ;
}