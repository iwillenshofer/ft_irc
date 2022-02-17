/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_links.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:07 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/16 19:44:08 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_links(void)
{
	std::string nick;
	IrcClient c(_host, _port);

	title("links");
	description("Testing links...");
	c.command("PASS " + _password + "\r\n", false);
	c.command("USER client1 8 * :Client Name\r\n", false);
	c.command("NICK client1\r\n", false);
	c.listen(false);
	c.command("LINKS unknown_server\r\n");
	c.listen();
	c.command("LINKS unknown_server not_a_server\r\n");
	c.listen();
	c.command("LINKS unknown_server irc.42network.com\r\n");
	c.listen();
	c.command("LINKS *.edu *.com\r\n");
	c.listen();
	c.command("LINKS irc.42network.com *.edu\r\n");
	c.listen();
	c.command("LINKS *.edu\r\n");
	c.listen();
	c.command("LINKS irc.42network.com irc.42network.com\r\n");
	c.listen();
	c.command("LINKS irc.42network.com *\r\n");
	c.listen();
	c.command("LINKS irc.42network.com *.com\r\n");
	c.listen();
	c.command("LINKS *.com\r\n");
	c.listen();
	c.command("LINKS\r\n");
	c.listen();
}
