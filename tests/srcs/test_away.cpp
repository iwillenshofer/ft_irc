/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_away.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:20:43 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/22 20:05:44 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"


void Tester::test_away(void)
{
	std::string nick;

	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	title("away");
	description("Testing away");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client1 8 * :Client1 Name\r\n");
	c1.command("NICK client1\r\n");
	c1.listen(false);

	c.command("JOIN #channel\r\n");
	c.listen(false);

	c1.command("MODE client1 -i\r\n");
	c1.command("AWAY :I'm away\r\n");
	c1.listen(false);

	c.command("INVITE client1 #channel\r\n");
	c.listen();
	c1.listen();

	c.command("PRIVMSG client1 :HELLO THERE\r\n");
	c.listen();
	c1.listen();

	c.command("WHOIS client1\r\n");
	c.listen();
	c1.listen();
}
