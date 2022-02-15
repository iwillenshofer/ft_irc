/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ping.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:38 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 21:34:01 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_ping(void)
{
	IrcClient c(_host, _port);

	title("ping");
	description("Testing ping command");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("PING\r\n");
	c.listen();
	c.command("PING :hello there\r\n");
	c.listen();
	c.command("PING hello\r\n");
	c.listen();
	c.command("PING irc.42network.com irc.42network.com\r\n");
	c.listen();
}
