/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_privmsg.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:43 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 21:19:40 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_privmsg_away(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	description("Test sending message to an away user");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c1.command("PASS " + _password + "\r\n", false);
	c1.command("NICK client1\r\n", false);
	c1.command("USER username hostname servername realname\r\n", false);
	c1.listen(false);
	c1.command("AWAY :Be right back\r\n");
	c1.listen();
	c.command("PRIVMSG client1 :hello there\r\n");
	c.listen();
	c1.listen();
}

void Tester::test_privmsg_mask(void)
{
	IrcClient c(_host, _port);

	description("Testing privmsg masks");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("PRIVMSG $irc.42network.com :hello\r\n");
	c.listen();
	c.command("PRIVMSG $*.com :hello\r\n");
	c.listen();
}

void Tester::test_privmsg_nickname(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	description("Sending message to nickname");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c1.command("PASS " + _password + "\r\n", false);
	c1.command("NICK client1\r\n", false);
	c1.command("USER username hostname servername realname\r\n", false);
	c1.listen(false);
	c.command("PRIVMSG client1 :hello there\r\n");
	c.listen();
	c1.listen();
}


void Tester::test_privmsg_channel(void)
{
	IrcClient cl(_host, _port);
	IrcClient c[3];

	description("Sending message to channel");
	for (int i = 0; i < 3; i++)
	{
		c[i] = IrcClient(_host, _port);
		c[i].command("PASS " + _password + "\r\n", false);
		c[i].command("NICK client" + ft::to_string(i) + "\r\n", false);
		c[i].command("USER username hostname servername realname\r\n", false);
		c[i].listen(false);
		c[i].command("JOIN #channel\r\n", false);		
		c[i].listen(false);
	}

	cl.command("PASS " + _password + "\r\n");
	cl.command("NICK client\r\n");
	cl.command("USER username hostname servername realname\r\n", false);
	cl.listen(false);
	cl.command("JOIN #channel\r\n", false);
	cl.listen();
	for (int i = 0; i < 3; i++)
		c[i].listen(false);
	cl.command("PRIVMSG #channel :hello there!\r\n");
	cl.listen();
	for (int i = 0; i < 3; i++)
		c[i].listen();
}

void Tester::test_privmsg_exceptions(void)
{
	IrcClient c(_host, _port);

	description("Testing privmsg exceptions");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.command("JOIN #channel\r\n", false);
	c.listen(false);
	c.command("PRIVMSG unknown\r\n");
	c.listen();
	c.command("PRIVMSG unknown :Hello!\r\n");
	c.listen();
	c.command("PRIVMSG #unknown :Hello!\r\n");
	c.listen();
	c.command("PRIVMSG #*.com :Hello!\r\n");
	c.listen();
	c.command("PRIVMSG $*.edu :Hello!\r\n");
	c.listen();
}

void Tester::test_privmsg(void)
{
	title("privmsg");
	test_privmsg_exceptions();
	test_privmsg_mask();
	test_privmsg_channel();
	test_privmsg_nickname();
	test_privmsg_away();
}
