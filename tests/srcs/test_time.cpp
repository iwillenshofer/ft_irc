/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_time.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:58 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 19:29:13 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_time(void)
{
	title("time");
	IrcClient c(_host, _port);

	description("Testing server time");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("TIME\r\n");
	c.listen();
	c.command("TIME irc.42network.com\r\n");
	c.listen();
	c.command("TIME irc.unknownserver.com\r\n");
	c.listen();
}
