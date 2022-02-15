/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pong.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:41 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 21:16:09 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_pong(void)
{
	IrcClient c(_host, _port);

	title("pong");
	description("Testing pong command");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("PONG\r\n");
	c.listen();
	c.command("PONG irc.42network.com unknown_server\r\n");
	c.listen();
	c.command("PONG :hello\r\n");
	c.listen();
	c.command("PONG irc.42network.com irc.42network.com\r\n");
	c.listen();
}
