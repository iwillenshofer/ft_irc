/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stats.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:55 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 20:46:45 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_stats(void)
{
	IrcClient c(_host, _port);

	title("stats");
	description("Testing server stats");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("STATS\r\n");
	c.listen();
	c.command("STATS irc.42network.com\r\n");
	c.listen();
	c.command("STATS irc.unknownserver.com\r\n");
	c.listen();
	c.command("STATS m irc.unknownserver.com\r\n");
	c.listen();
	c.command("STATS m irc.42network.com\r\n");
	c.listen();
	c.command("STATS m\r\n");
	c.listen();
	c.command("STATS o\r\n");
	c.listen();
	c.command("STATS u\r\n");
	c.listen();
}
