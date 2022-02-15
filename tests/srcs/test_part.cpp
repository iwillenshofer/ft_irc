/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_part.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:33 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 22:13:50 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_part_exceptions(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	description("Testing part exceptions. ");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c1.command("PASS " + _password + "\r\n", false);
	c1.command("NICK client1\r\n", false);
	c1.command("USER username hostname servername realname\r\n", false);
	c1.command("JOIN #channel\r\n", false);
	c1.listen(false);
	c.command("PART\r\n");
	c.listen();
	c.command("PART #channel2\r\n");
	c.listen();
	c.command("PART #channel\r\n");
	c.listen();
}

void Tester::test_part_success(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	description("Testing part exceptions. ");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("JOIN #channel1,#channel2,#channel3\r\n", false);
	c.listen(false);
	c1.command("PASS " + _password + "\r\n", false);
	c1.command("NICK client2\r\n", false);
	c1.command("USER username hostname servername realname\r\n", false);
	c1.listen(false);
	c1.command("JOIN  #channel1,#channel2,#channel3\r\n", false);
	c1.listen(false);
	c.listen();
	c1.command("PART #channel1\r\n");
	c.listen();
	c1.listen();
	c1.command("PART #channel2,#channel3\r\n");
	c.listen();
	c1.listen();
}

void Tester::test_part(void)
{
	title("part");
	test_part_exceptions();
	test_part_success();
}
