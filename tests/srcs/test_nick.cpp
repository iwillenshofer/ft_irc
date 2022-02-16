/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_nick.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:24 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 21:27:48 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_nick(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	title("nick");
	description("Testing oper command success and notice to other opers");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c1.command("PASS " + _password + "\r\n", false);
	c1.command("NICK client2\r\n", false);
	c1.command("USER username hostname servername realname\r\n", false);
	c1.listen(false);
	c.command("NICK\r\n");
	c.listen();
	c.command("NICK ''\r\n");
	c.listen();
	c.command("NICK client2\r\n");
	c.listen();
	c.command("NICK #whatever\r\n");
	c.listen();
	c.command("NICK nick*i?\r\n");
	c.listen();
	c.command("NICK longnick11\r\n");
	c.listen();
	c.command("NICK maxnicksz\r\n");
	c.listen();
}
