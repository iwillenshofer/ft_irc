/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_kick.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:02 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/21 20:48:23 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_kick(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);

	title("kick");
	description("Testing kick command");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.command("JOIN #channel\r\n", false);
	c.command("JOIN #channel2\r\n", false);
	c.listen(false);
	c1.command("PASS " + _password + "\r\n", false);
	c1.command("NICK client2\r\n", false);
	c1.command("USER username hostname servername realname\r\n", false);
	c1.command("JOIN #channel\r\n", false);
	c1.command("JOIN #channel2\r\n", false);
	c1.command("JOIN #channel3\r\n", false);
	c1.listen(false);
	c.command("JOIN #channel3\r\n", false);
	c.listen(false);
	c1.listen(false);
	c.command("KICK\r\n");
	c.listen();
	c.command("KICK #channel\r\n");
	c.listen();
	c.command("KICK #channel unknown\r\n");
	c.listen();
	c1.listen();
	c.command("KICK #unknown client2\r\n");	
	c.listen();
	c1.listen();
	c.command("KICK #channel3 client2\r\n");
	c.listen();
	c1.listen();
	c.command("KICK #cha!nnel2 client2\r\n");
	c.listen();
	c1.listen();
	c.command("KICK #channel2 client2\r\n");
	c.listen();
	c1.listen();
	c.command("KICK #channel,#channel3 client,client2 :bye bye!\r\n");
	c.listen();
	c1.listen();
}
