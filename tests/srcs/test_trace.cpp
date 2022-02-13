/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_trace.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:07:19 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/12 21:24:00 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_trace_server(void)
{
	std::string nick;
	IrcClient c(_host, _port);

	description("Testing trace command.");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n");
	c.listen(false);
	c.command("TRACE\r\n");
	c.listen(true);
	c.command("OPER iwillens Igor123\r\n");
	c.listen(true);
	c.command("TRACE\r\n");
	c.listen();
	c.command("TRACE *\r\n");
	c.listen();
	c.command("TRACE irc.unknown.com\r\n");
	c.listen();
	c.command("TRACE irc.42network.com\r\n");
	c.listen();
}

void Tester::test_trace(void)
{
	title("trace");
	test_trace_server();
}
