/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_info.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:20:55 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 20:23:22 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_info_no_ircop(void)
{
	std::string nick;

	IrcClient c(_host, _port);
	description("Performs tests when user is not an IRC OP");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c.command("INFO\r\n");
	c.listen();
	c.command("INFO test\r\n");
	c.listen();
	c.command("INFO irc.42network.com\r\n");
	c.listen();
	c.command("INFO *42network.com\r\n");
	c.listen();
}

void Tester::test_info_ircop(void)
{
	std::string nick;

	IrcClient c(_host, _port);
	description("Performs tests when user is an IRC OP");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c.command("OPER robitett Roman123\r\n");
	c.listen(false);

	c.command("INFO\r\n");
	c.listen();
	c.command("INFO test\r\n");
	c.listen();
	c.command("INFO irc.42network.com\r\n");
	c.listen();
	c.command("INFO *42network.com\r\n");
	c.listen();
}

void Tester::test_info(void)
{
	title("info");
	test_info_ircop();
	test_info_no_ircop();
}