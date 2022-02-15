/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_quit.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:46 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 19:12:59 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_quit(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	title("quit");
	description("Testing quit command");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("JOIN #channel\r\n", false);
	c1.command("PASS " + _password + "\r\n");
	c1.command("NICK client2\r\n");
	c1.command("USER username hostname servername realname\r\n", false);
	c1.command("JOIN #channel\r\n", false);
	c1.listen(false);
	c.listen(false);
	c.command("QUIT\r\n");
	c.listen();
	c1.listen();
	c1.command("QUIT :bye bye\r\n");
	c1.listen();
}
