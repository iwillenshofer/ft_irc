/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_invite.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:20:57 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 22:49:42 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_invite_no_user_no_channel(void)
{
	std::string nick;

	IrcClient c(_host, _port);
	description("Performs tests when there is no user to invite and no valid channel");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c.command("INVITE\r\n");
	c.listen();
	c.command("INVITE nickname\r\n");
	c.listen();
	c.command("INVITE nickname #channel\r\n");
	c.listen();
}

void Tester::test_invite_user_no_channel(void)
{
	std::string nick;

	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	description("Performs tests when there is a user to invite and no valid channel");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER nickname 8 * :Nick Name\r\n");
	c1.command("NICK nickname\r\n");
	c1.listen(false);

	c.command("INVITE\r\n");
	c.listen();
	c.command("INVITE nickname\r\n");
	c.listen();
	c.command("INVITE nickname #channel\r\n");
	c.listen();
}

void Tester::test_invite_channel_no_user(void)
{
	std::string nick;

	IrcClient c(_host, _port);
	description("Performs tests when there is no user to invite and a valid channel");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c.command("JOIN #channel\r\n");
	c.listen(false);
	c.command("INVITE\r\n");
	c.listen();
	c.command("INVITE nickname\r\n");
	c.listen();
	c.command("INVITE nickname #channel\r\n");
	c.listen();
}

void Tester::test_invite_no_chanop(void)
{
	std::string nick;

	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	IrcClient c2(_host, _port);
	description("Performs tests when arguments are valid but sender is not chanop");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client1 8 * :Client1 Name\r\n");
	c1.command("NICK client1\r\n");
	c1.listen(false);

	c2.command("PASS " + _password + "\r\n");
	c2.command("USER client2 8 * :Client2 Name\r\n");
	c2.command("NICK client2\r\n");
	c2.listen(false);

	c.command("JOIN #channel\r\n");
	c.listen(false);
	c1.command("INVITE client2 #channel\r\n");
	c1.listen();
	c1.command("JOIN #channel\r\n");
	c1.listen(false);
	c1.command("INVITE client2 #channel\r\n");
	c1.listen();
}

void Tester::test_invite_chanop(void)
{
	std::string nick;

	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	description("Performs tests when arguments are valid and sender is chanop");

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
	c.command("INVITE client1 #channel\r\n");
	c.listen();
	c1.listen();
}

void Tester::test_invite_away(void)
{
	std::string nick;

	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	description("Performs tests when arguments are valid and sender is chanop");

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

	c1.command("AWAY I'm away\r\n");
	c1.listen(false);

	c.command("INVITE client1 #channel\r\n");
	c.listen();
	c1.listen();
}

void Tester::test_invite(void)
{
	title("invite");
	test_invite_no_user_no_channel();
	test_invite_user_no_channel();
	test_invite_channel_no_user();
	test_invite_no_chanop();
	test_invite_chanop();
	test_invite_away();
}
