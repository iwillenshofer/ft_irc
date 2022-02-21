/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_admin.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:20:43 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/21 20:47:48 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_admin_no_ircop(void)
{
	std::string nick;

	IrcClient c(_host, _port);
	description("Performs tests when user is not an IRC OP");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c.command("ADMIN\r\n");
	c.listen();
	c.command("ADMIN other_srv\r\n");
	c.listen();
	c.command("ADMIN irc.42network.com\r\n");
	c.listen();
	c.command("ADMIN *42network.com\r\n");
	c.listen();
}

void Tester::test_admin_ircop(void)
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

	c.command("ADMIN\r\n");
	c.listen();
	c.command("ADMIN other_srv\r\n");
	c.listen();
	c.command("ADMIN irc.42network.com\r\n");
	c.listen();
	c.command("ADMIN *42network.com\r\n");
	c.listen();
}

void Tester::test_admin(void)
{
	title("admin");
	test_admin_ircop();
	test_admin_no_ircop();
}
