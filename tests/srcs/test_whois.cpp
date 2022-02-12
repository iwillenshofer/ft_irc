/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_whois.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 00:21:31 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/12 17:45:00 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_whois_visibility(void)
{
	IrcClient c0(_host, _port);
	IrcClient c1(_host, _port);

	description("Performs whois to an invisible user. Then, make it visible and try again. "
					"Once more, make it invisible and try again.");
	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client1 8 * :Client One\r\n");
	c1.command("NICK client1\r\n");
	c1.listen(false);
	c0.command("PASS " + _password + "\r\n");
	c0.command("USER client0 8 * :Client Zero\r\n");
	c0.command("NICK client0\r\n");
	c0.listen(false);
	c0.command("WHOIS client1\r\n");
	c0.listen();
	c1.command("MODE client1 -i\r\n");
	c1.listen();
	c0.command("WHOIS client1\r\n");
	c0.listen();
	c1.command("MODE client1 +i\r\n");
	c1.listen();
	c0.command("WHOIS client1\r\n");
	c0.listen();
}

void Tester::test_whois_invalidusername(void)
{
	IrcClient c0(_host, _port);
	description("Performs whois to some invalid and unknown nicknames.");
	c0.command("PASS " + _password + "\r\n");
	c0.command("USER client 8 * :Client Name\r\n");
	c0.command("NICK client\r\n");
	c0.listen(false);
	c0.command("WHOIS #hello\r\n");
	c0.listen();
	c0.command("WHOIS !@&!@!\r\n");
	c0.listen();
	c0.command("WHOIS unknown\r\n");
	c0.listen();
}

void Tester::test_whois_no_parameters(void)
{
	IrcClient c0(_host, _port);
	description("Performs whois with no parameters.");
	c0.command("PASS " + _password + "\r\n");
	c0.command("USER client 8 * :Client Name\r\n");
	c0.command("NICK client\r\n");
	c0.listen(false);
	c0.command("WHOIS\r\n");
	c0.listen();
}

void Tester::test_whois_masks(void)
{
	std::string nick;

	IrcClient c[6];
	IrcClient c0(_host, _port);
	description("Performs whois, with visible users using with nickname masks.");
	for (int i = 0; i < 6; i++)
	{
		nick = ((i < 2) ? "client" : "otclient");
		nick += ft::to_string(i);
		c[i] = IrcClient(_host, _port);
		c[i].command("PASS " + _password + "\r\n", false);
		c[i].command("USER " + nick + " 8 * :Client Name\r\n", false);
		c[i].command("NICK " + nick + "\r\n", false);
		c[i].command("MODE " + nick + " -i\r\n", false);
		c[i].listen(false);
	}
	c0.command("PASS " + _password + "\r\n");
	c0.command("USER client 8 * :Client Name\r\n");
	c0.command("NICK client\r\n");
	c0.listen(false);
	c0.command("WHOIS *\r\n");
	c0.listen();
	c0.command("WHOIS *client*\r\n");
	c0.listen();
	c0.command("WHOIS *ot*\r\n");
	c0.listen();
	c0.command("WHOIS ot*\r\n");
	c0.listen();
}

void	Tester::test_whois_misc()
{
	IrcClient c0(_host, _port);
	IrcClient c1(_host, _port);

	description("Performs whois, when other user is visible, operator.");
	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client1 8 * :Client One\r\n");
	c1.command("NICK client1\r\n");
	c1.listen(false);
	c1.command("OPER iwillens Igor123\r\n");
	c1.command("MODE client1 -i\r\n");
	c1.command("MODE client1 +a :I'm away\r\n");
	c1.listen(false);
	c0.command("PASS " + _password + "\r\n");
	c0.command("USER client0 8 * :Client Zero\r\n");
	c0.command("NICK client0\r\n");
	c0.listen(false);
	c0.command("WHOIS client1\r\n");
	c0.listen();
}

void Tester::test_whois_samechannel(void)
{
	std::string nick;

	IrcClient c0(_host, _port);
	IrcClient c[5];
	description("Performs whois, with invisible users but in the same channel.");
	for (int i = 0; i < 5; i++)
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
	c0.command("WHOIS *\r\n");
	c0.listen();
	for (int i = 0; i < 5; i++)
	{
		c[i].command("JOIN #channel\r\n");
		c[i].listen(false);
	}
	c0.command("JOIN #channel\r\n");
	c0.listen(false);
	c0.command("WHOIS *\r\n");
	c0.listen();
}

void Tester::test_whois(void)
{
	title("Whois");
	test_whois_invalidusername();
	test_whois_no_parameters();
	test_whois_visibility();
	test_whois_masks();
	test_whois_misc();
	test_whois_samechannel();
}
