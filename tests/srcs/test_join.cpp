/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_join.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:00 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/16 19:17:45 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_join_ERR_NEEDMOREPARAMS(void)
{
	IrcClient c(_host, _port);
	description("Performs tests when parameters are missing.");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c.command("JOIN\r\n");
	c.listen();
}

void Tester::test_join_ERR_INVITEONLYCHAN(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	description("Performs tests when channel is invitation only.");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client1 8 * :Client1 Name\r\n");
	c1.command("NICK client1\r\n");
	c1.listen(false);

	c.command("JOIN #test\r\n");
	c.listen(false);
	c.command("MODE #test +i\r\n");
	c.listen(false);

	c1.command("JOIN #test\r\n");
	c1.listen();
}

void Tester::test_join_ERR_CHANNELISFULL(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	description("Performs tests when channel limit is full.");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client1 8 * :Client1 Name\r\n");
	c1.command("NICK client1\r\n");
	c1.listen(false);

	c.command("JOIN #test\r\n");
	c.listen(false);
	c.command("MODE #test +l 1\r\n");
	c.listen(false);

	c1.command("JOIN #test\r\n");
	c1.listen();
}

void Tester::test_join_ERR_NOSUCHCHANNEL(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	description("Performs tests when channel's name is invalid.");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);
	
	c.command("JOIN InvalidChannel\r\n");
	c.listen();
}

void Tester::test_join_ERR_BANNEDFROMCHAN(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	description("Performs tests when user is banned from the channel.");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client1 8 * :Client1 Name\r\n");
	c1.command("NICK client1\r\n");
	c1.listen(false);

	c.command("JOIN #test\r\n");
	c.listen(false);
	c.command("MODE #test +b *lient1\r\n");
	c.listen(false);

	c1.command("JOIN #test\r\n");
	c1.listen();
}

void Tester::test_join_ERR_BADCHANNELKEY(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	description("Performs tests when channel key is invalid.");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client1 8 * :Client1 Name\r\n");
	c1.command("NICK client1\r\n");
	c1.listen(false);

	c.command("JOIN #test\r\n");
	c.listen(false);
	c.command("MODE #test +k pass\r\n");
	c.listen();

	c1.command("JOIN #test\r\n");
	c1.listen();

	c1.command("JOIN #test badpass\r\n");
	c1.listen();

	c1.command("JOIN #test pass\r\n");
	c1.listen();
}

void Tester::test_join_few_channels(void)
{
	IrcClient c(_host, _port);
	description("Performs tests when user try to join fews channels in the same time.");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c.command("JOIN #test,#test1,test2\r\n");
	c.listen();
}

void Tester::test_join_few_channels_password(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	description("Performs tests when user try to join fews channels with password in the same time.");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client1 8 * :Client1 Name\r\n");
	c1.command("NICK client1\r\n");
	c1.listen(false);

	c.command("JOIN #test1\r\n");
	c.command("MODE #test1 +k pass1\r\n");
	c.command("JOIN #test2\r\n");
	c.command("MODE #test2 +k pass2\r\n");
	c.listen(false);

	c1.command("JOIN #test1,#test2 wrongpass1,wrongpass2\r\n");
	c1.listen();

	c1.command("JOIN #test1,#test2 pass1,pass2\r\n");
	c1.listen();
}

void Tester::test_join_special_argument_0(void)
{
	IrcClient c(_host, _port);
	description("Performs tests when user try leave all the channels with the special argument 0.");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);

	c.command("JOIN #test1,#test2,#test3,#test4\r\n");
	c.listen(false);

	c.command("JOIN 0\r\n");
	c.listen();
}

void Tester::test_join(void)
{
	title("join");
	test_join_ERR_NEEDMOREPARAMS();
	test_join_ERR_INVITEONLYCHAN();
	test_join_ERR_CHANNELISFULL();
	test_join_ERR_NOSUCHCHANNEL();
	test_join_ERR_BANNEDFROMCHAN();
	test_join_ERR_BADCHANNELKEY();
	test_join_few_channels();
	test_join_few_channels_password();
	test_join_special_argument_0();
}
