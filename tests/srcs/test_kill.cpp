/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_kill.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:04 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/16 19:52:46 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_kill(void)
{
	title("kill");
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	description("Testing kill command with and without OPER");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c1.command("PASS " + _password + "\r\n", false);
	c1.command("NICK client2\r\n", false);
	c1.command("USER username hostname servername realname\r\n", false);
	c1.listen(false);
	c.command("KILL\r\n");
	c.listen();
	c.command("KILL client2\r\n");
	c.listen();
	c.command("KILL client2 :bye bye\r\n");
	c.listen();
	c.command("OPER iwillens Igor123\r\n");
	c.listen();
	c.command("KILL unknown :bye bye\r\n");
	c.listen();
	c.command("KILL client2 :bye bye\r\n");
	c.listen();
	c1.listen();
}
