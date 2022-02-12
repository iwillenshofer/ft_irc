/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_whowas.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 00:21:31 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/12 18:06:15 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_whowas_no_parameters(void)
{
	IrcClient c0(_host, _port);
	description("Performs whowas with no parameters.");
	c0.command("PASS " + _password + "\r\n");
	c0.command("USER client 8 * :Client Name\r\n");
	c0.command("NICK client\r\n");
	c0.listen(false);
	c0.command("WHOWAS\r\n");
	c0.listen();
}

void Tester::test_whowas_invalidusername(void)
{
	IrcClient c0(_host, _port);
	description("Performs whowas to some invalid and unknown nicknames.");
	c0.command("PASS " + _password + "\r\n");
	c0.command("USER client 8 * :Client Name\r\n");
	c0.command("NICK client\r\n");
	c0.listen(false);
	c0.command("WHOWAS #hello\r\n");
	c0.listen();
	c0.command("WHOWAS !@&!@!\r\n");
	c0.listen();
	c0.command("WHOWAS unknown\r\n");
	c0.listen();
}

void Tester::test_whowas_clients(void)
{
	std::string nick;

	IrcClient c0(_host, _port);
	IrcClient c[5];
	description("Performs whowas on sigle user, multiple users and limiting count");
	for (int i = 0; i < 3; i++)
	{
		nick = "client";
		nick += ft::to_string(i);
		c[i] = IrcClient(_host, _port);
		c[i].command("PASS " + _password + "\r\n", false);
		c[i].command("USER " + nick + " 8 * :Client Name\r\n", false);
		c[i].command("NICK " + nick + "\r\n", false);
		c[i].listen(false);
	}
	c0.command("PASS " + _password + "\r\n");
	c0.command("USER client 8 * :Client Name\r\n");
	c0.command("NICK client\r\n");
	c0.listen(false);
	c0.command("WHOWAS client1\r\n");
	c0.listen();
	c0.command("WHOWAS client1,client2,client0\r\n");
	c0.listen();
	c0.command("WHOWAS client1,unknown,client0\r\n");
	c0.listen();
	c0.command("WHOWAS client1,client2,client0 3\r\n");
	c0.listen();
}

void Tester::test_whowas(void)
{
	title("Whowas");
	test_whowas_invalidusername();
	test_whowas_no_parameters();
	test_whowas_clients();
}
