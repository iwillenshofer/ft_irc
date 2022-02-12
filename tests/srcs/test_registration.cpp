/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_registration.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 20:46:23 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/12 00:50:49 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_registration_timeout(void)
{
	IrcClient c0(_host, _port);

	description("Stalling in Registration until timeout");
	c0.command("PASS " + _password + "\r\n");
	c0.command("NICK client\r\n");
	while (c0.is_connected())
		c0.listen();
}

void Tester::test_registration_nicknameinuse_retry(void)
{
	IrcClient c0(_host, _port);
	IrcClient c1(_host, _port);

	description("Trying to join with a nickname already in use and retry after changing it");
	c0.command("PASS " + _password + "\r\n");
	c0.command("NICK client\r\n");
	c0.command("USER client 0 * :Client Name\r\n");
	c0.listen();
	c1.command("PASS " + _password + "\r\n");
	c1.command("NICK client\r\n");
	c1.command("USER client 0 * :Client Name\r\n");
	c1.listen();
	c1.command("NICK client2\r\n");
	c0.listen();
	c1.listen();
}

void Tester::test_registration_nicknameinuse(void)
{
	IrcClient c0(_host, _port);
	IrcClient c1(_host, _port);

	description("Trying to join with a nickname already in use");
	c0.command("PASS " + _password + "\r\n");
	c0.command("NICK client\r\n");
	c0.command("USER client 0 * :Client Name\r\n");
	c1.command("PASS haha\r\n");
	c1.command("NICK client\r\n");
	c1.command("USER client 0 * :Client Name\r\n");
	c1.listen();
}

void Tester::test_registration_full(void)
{
	IrcClient c0(_host, _port);
	description("Performing full registration");
	c0.command("PASS " + _password + "\r\n");
	c0.command("NICK client\r\n");
	c0.command("USER client 0 * :Client Name\r\n");
	c0.listen();
}

void Tester::test_registration_invalid_password(void)
{
	IrcClient c0(_host, _port);
	description("Trying to register with an invalid password.");
	c0.command("PASS wrong" + _password + "\r\n");
	c0.command("NICK wrongpass\r\n");
	c0.command("USER wrongpass 0 * :Wrong Pass\r\n");
	c0.listen();
}

void Tester::test_registration_command(void)
{
	IrcClient c0(_host, _port);
	description("Testing a command without being registered at the server yet.");
	c0.command("JOIN #brasil\r\n");
	c0.listen();
}

void Tester::test_registration(void)
{
	title("Registration");
	test_registration_invalid_password();
	test_registration_command();
	test_registration_full();
	test_registration_nicknameinuse();
	test_registration_nicknameinuse_retry();
	test_registration_timeout();
}
