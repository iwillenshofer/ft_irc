/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_who.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 00:21:31 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/12 20:29:03 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_who_channel(void)
{
	std::string nick;

	IrcClient c[6];
	IrcClient c0(_host, _port);
	description("Performs who, with visible users using with nickname masks.");
	for (int i = 0; i < 6; i++)
	{
		nick = ((i < 2) ? "client" : "otclient");
		nick += ft::to_string(i);
		c[i] = IrcClient(_host, _port);
		c[i].command("PASS " + _password + "\r\n", false);
		c[i].command("USER " + nick + " 8 * :Client Name\r\n", false);
		c[i].command("NICK " + nick + "\r\n", false);
		c[i].listen(false);
		c[i].command("JOIN #channel\r\n", true);
		c[i].listen(false);
	}
	c0.command("PASS " + _password + "\r\n");
	c0.command("USER client 8 * :Client Name\r\n");
	c0.command("NICK client\r\n");
	c0.listen(false);
	c0.command("WHO #channel\r\n");
	c0.listen();
	c0.command("JOIN #channel\r\n", true);
	c0.listen(false);
	c0.command("WHO #channel\r\n");
	c0.listen();
}

void Tester::test_who_masks(void)
{
	std::string nick;

	IrcClient c[6];
	IrcClient c0(_host, _port);
	description("Performs who, with visible users using with nickname masks.");
	for (int i = 0; i < 6; i++)
	{
		nick = ((i < 2) ? "client" : "otclient");
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
	c0.command("WHO *\r\n");
	c0.listen();
	for (int i = 0; i < 6; i++)
	{
		nick = ((i < 2) ? "client" : "otclient");
		nick += ft::to_string(i);
		c[i].command("MODE " + nick + " -i\r\n", true);
		c[i].listen(false);
	}
	c0.command("WHO *\r\n");
	c0.listen();
	c0.command("WHO *client*\r\n");
	c0.listen();
	c0.command("WHO *ot*\r\n");
	c0.listen();
	c0.command("WHO ot*\r\n");
	c0.listen();
}

void Tester::test_who(void)
{
	title("Who");
	test_who_masks();
	test_who_channel();
}































