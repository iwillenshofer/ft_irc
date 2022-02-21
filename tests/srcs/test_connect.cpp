/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_connect.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:20:49 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/21 20:47:57 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_connect_no_ircop(void)
{
	std::string nick;

	IrcClient c(_host, _port);
	description("Performs tests when user is not an IRC OP");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c.command("CONNECT\r\n");
	c.listen();
	c.command("CONNECT test1\r\n");
	c.listen();
	c.command("CONNECT test1 test2\r\n");
	c.listen();
	c.command("CONNECT test1 test2 test3\r\n");
	c.listen();
	c.command("CONNECT test1 test2 irc.42network.com\r\n");
	c.listen();
}

void Tester::test_connect_ircop(void)
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

	c.command("CONNECT\r\n");
	c.listen();
	c.command("CONNECT test1\r\n");
	c.listen();
	c.command("CONNECT test1 test2\r\n");
	c.listen();
	c.command("CONNECT test1 test2 test3\r\n");
	c.listen();
	c.command("CONNECT test1 test2 irc.42network.com\r\n");
	c.listen();
}

void Tester::test_connect(void)
{
	title("connect");
	test_connect_ircop();
	test_connect_no_ircop();
}
