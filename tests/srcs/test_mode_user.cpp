/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mode_user.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:17 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/17 22:45:21 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_mode_i(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	description("Testing mode user invisible command");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c1.command("PASS " + _password + "\r\n", false);
	c1.command("NICK client1\r\n", false);
	c1.command("USER username hostname servername realname\r\n", false);
	c1.listen(false);
	c.command("WHOIS client1\r\n");
	c.listen();
	c1.command("MODE client1 -i\r\n");
	c1.listen();
	c.command("WHOIS client1\r\n");
	c.listen();
}

void Tester::test_mode_o(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	description("Testing mode user operator command");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c1.command("PASS " + _password + "\r\n", false);
	c1.command("NICK client1\r\n", false);
	c1.command("USER username hostname servername realname\r\n", false);
	c1.listen(false);
	c.command("KILL client1 :bye\r\n");
	c.listen();
	c1.listen();
	c.command("OPER iwillens Igor123\r\n");
	c.listen();
	c.command("KILL client1 :bye\r\n");
	c.listen();
	c1.listen();
	c.command("MODE client -o\r\n");
	c.listen();
}

void Tester::test_mode_exceptions(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	description("Testing mode user command exceptions");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c1.command("PASS " + _password + "\r\n", false);
	c1.command("NICK client1\r\n", false);
	c1.command("USER username hostname servername realname\r\n", false);
	c1.listen(false);
	c.command("MODE\r\n");
	c.listen();
	c.command("MODE otheruser\r\n");
	c.listen();
	c.command("MODE client1\r\n");
	c.listen();
	c.command("MODE client +o\r\n");
	c.listen();
	c.command("MODE client Z\r\n");
	c.listen();
	c.command("MODE client * *\r\n");
	c.listen();
	c.command("MODE client +Awjidsam,.zvç\r\n");
	c.listen();
}

void Tester::test_mode_success(void)
{
	IrcClient c(_host, _port);

	description("Testing mode user command success");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("MODE client -wiso\r\n");
	c.listen();
	c.command("MODE client +wiso\r\n");
	c.listen();
	c.command("MODE client -wiso\r\n");
	c.listen();
	c.command("MODE client +i\r\n");
	c.listen();
	c.command("MODE client -i\r\n");
	c.listen();
	c.command("MODE client +s\r\n");
	c.listen();
	c.command("MODE client -s\r\n");
	c.listen();
	c.command("MODE client +w\r\n");
	c.listen();
	c.command("MODE client -w\r\n");
	c.listen();
	c.command("OPER iwillens Igor123\r\n");
	c.listen();
	c.command("MODE client +wiso\r\n");
	c.listen();
	c.command("MODE client -s\r\n");
	c.listen();
	c.command("MODE client +s\r\n");
	c.listen();
	c.command("MODE client -o\r\n");
	c.listen();
	c.command("MODE client -wiso\r\n");
	c.listen();
}

void Tester::test_mode_user(void)
{
	title("mode_user");
	test_mode_exceptions();
	test_mode_success();
	test_mode_o();
	test_mode_i();
}

