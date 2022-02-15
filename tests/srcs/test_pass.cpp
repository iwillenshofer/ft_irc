/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:35 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 21:47:01 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_pass_exceptions(void)
{
	IrcClient c(_host, _port);

	description("Testing password exceptions. ");
	c.command("PASS\r\n");
	c.listen();
	c.command("PASS unknown_pass\r\n");
	c.listen();
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen();
}

void Tester::test_pass_registered(void)
{
	IrcClient c(_host, _port);

	description("Testing password succesfully, and when already registered. ");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.listen();
	c.command("PASS unknown_pass\r\n");
	c.listen();
}

void Tester::test_pass(void)
{
	title("pass");
	test_pass_exceptions();
	test_pass_registered();
}

