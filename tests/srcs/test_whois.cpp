/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_whois.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 00:21:31 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/12 00:52:18 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_whois_visibility(void)
{
	IrcClient c0(_host, _port);
	IrcClient c1(_host, _port);

	description("Performs whois to an invisible user. Then, make it visible and try again.");
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

void Tester::test_whois(void)
{
	title("Whois");
	test_whois_invalidusername();
	test_whois_visibility();
}
