/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_topic.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:07:11 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 19:30:25 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_priviledged(void)
{
	IrcClient c(_host, _port);

	description("Testing topic while succesfully changing the topic.");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n");
	c.listen(false);
	c.command("JOIN #channel\r\n");
	c.listen(true);
	c.command("MODE #channel +t client\r\n");
	c.listen(true);
	c.command("TOPIC #channel HELLO!\r\n");
	c.listen(true);
	c.command("MODE #channel -o client\r\n");
	c.listen(true);
	c.command("TOPIC #channel HELLO 2!\r\n");
	c.listen(true);
	c.command("TOPIC #channel\r\n");
	c.listen(true);

}

void Tester::test_success(void)
{
	IrcClient c(_host, _port);

	description("Testing topic while succesfully changing the topic.");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n");
	c.listen(false);
	c.command("JOIN #channel\r\n");
	c.listen(true);
	c.command("MODE #channel -o client\r\n");
	c.listen(true);
	c.command("TOPIC #channel\r\n");
	c.listen(true);
	c.command("TOPIC #channel HELLO!\r\n");
	c.listen(true);
	c.command("TOPIC #channel\r\n");
	c.listen(true);
}

void Tester::test_exceptions(void)
{
	IrcClient c(_host, _port);

	description("Testing topic command exceptions, as sending no parameters, "
				"or trying to change the topic without being on channel");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("TOPIC\r\n");
	c.listen();
	c.command("TOPIC #channel\r\n");
	c.listen();
	c.command("TOPIC #channel HELLO!\r\n");
	c.listen();
}


void Tester::test_topic(void)
{
	std::string nick;

	title("topic");
	test_exceptions();
	test_success();
	test_priviledged();
}
