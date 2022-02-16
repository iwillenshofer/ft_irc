/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_notice.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:27 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 21:19:32 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_notice_away(void)
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
	c.command("NOTICE client1 :hello there\r\n");
	c.listen();
	c1.listen();
}

void Tester::test_notice_mask(void)
{
	IrcClient c(_host, _port);

	description("Testing notice masks");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("NOTICE $irc.42network.com :hello\r\n");
	c.listen();
	c.command("NOTICE $*.com :hello\r\n");
	c.listen();
}

void Tester::test_notice_nickname(void)
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
	c.command("NOTICE client1 :hello there\r\n");
	c.listen();
	c1.listen();
}


void Tester::test_notice_channel(void)
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
	cl.command("NOTICE #channel :hello there!\r\n");
	cl.listen();
	for (int i = 0; i < 3; i++)
		c[i].listen();
}

void Tester::test_notice_exceptions(void)
{
	IrcClient c(_host, _port);

	description("Testing notice exceptions");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.command("JOIN #channel\r\n", false);
	c.listen(false);
	c.command("NOTICE unknown\r\n");
	c.listen();
	c.command("NOTICE unknown :Hello!\r\n");
	c.listen();
	c.command("NOTICE #unknown :Hello!\r\n");
	c.listen();
	c.command("NOTICE #*.com :Hello!\r\n");
	c.listen();
	c.command("NOTICE $*.edu :Hello!\r\n");
	c.listen();
}

void Tester::test_notice(void)
{
	title("notice");
	test_notice_exceptions();
	test_notice_mask();
	test_notice_channel();
	test_notice_nickname();
	test_notice_away();
}
