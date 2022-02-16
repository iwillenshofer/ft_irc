/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_oper.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:30 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 21:11:42 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_oper_success(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	description("Testing oper command success and notice to other opers");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c1.command("PASS " + _password + "\r\n", false);
	c1.command("NICK client2\r\n", false);
	c1.command("USER username hostname servername realname\r\n", false);
	c1.listen(false);
	c.command("OPER iwillens Igor123\r\n");
	c.listen();
	c1.command("OPER iwillens Igor123\r\n");
	c1.listen();
	c.listen();
}

void Tester::test_oper_exceptions(void)
{
	IrcClient c(_host, _port);
	
	description("Testing oper command exceptions");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("OPER\r\n");
	c.listen();
	c.command("OPER unknown\r\n");
	c.listen();
	c.command("OPER unknown wrongpass\r\n");
	c.listen();
	c.command("OPER iwillens wrongpass\r\n");
	c.listen();
}

void Tester::test_oper(void)
{
	title("oper");
	test_oper_exceptions();
	test_oper_success();
}
