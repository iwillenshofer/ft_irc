/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_squit.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:53 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 20:52:45 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_squit(void)
{
	IrcClient c(_host, _port);

	title("squit");
	description("Testing server squit");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("SQUIT\r\n");
	c.listen();
	c.command("OPER iwillens Igor123\r\n");
	c.listen();
	c.command("SQUIT\r\n");
	c.listen(false);
	c.command("SQUIT unknownserver\r\n");
	c.listen();
	c.command("SQUIT unknownserver :Bye\r\n");
	c.listen();
	c.command("SQUIT irc.42network.com :Bye\r\n");
	c.listen();
}
