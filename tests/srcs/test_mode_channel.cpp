/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mode_channel.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:14 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/17 21:40:05 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_mode_channel_b(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	IrcClient c2(_host, _port);
	description("Set a ban mask to keep users out");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client1 8 * :Client1 Name\r\n");
	c.command("NICK client1\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client2 8 * :Client2 Name\r\n");
	c1.command("NICK client2\r\n");
	c1.listen(false);

	c2.command("PASS " + _password + "\r\n");
	c2.command("USER client3 8 * :Client3 Name\r\n");
	c2.command("NICK client3\r\n");
	c2.listen(false);

	c.command("JOIN #test\r\n");
	c.listen(false);

	c1.command("JOIN #test\r\n");
	c1.listen(false);

	c1.command("MODE #test +b client3\r\n");
	c1.listen();

	c.command("MODE #test +b client3\r\n");
	c.listen();

	c2.command("JOIN #test\r\n");
	c2.listen();
}

void Tester::test_mode_channel_i(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	description("Invite-only channel flag");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client1 8 * :Client1 Name\r\n");
	c.command("NICK client1\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client2 8 * :Client2 Name\r\n");
	c1.command("NICK client2\r\n");
	c1.listen(false);

	c.command("JOIN #test\r\n");
	c.listen(false);

	c.command("MODE #test +i\r\n");
	c.listen();

	c1.command("JOIN #test\r\n");
	c1.listen();
}

void Tester::test_mode_channel_l(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	IrcClient c2(_host, _port);
	description("Set the user limit to channel");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client1 8 * :Client1 Name\r\n");
	c.command("NICK client1\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client2 8 * :Client2 Name\r\n");
	c1.command("NICK client2\r\n");
	c1.listen(false);

	c2.command("PASS " + _password + "\r\n");
	c2.command("USER client2 8 * :Client2 Name\r\n");
	c2.command("NICK client2\r\n");
	c2.listen(false);

	c.command("JOIN #test\r\n");
	c.listen(false);

	c.command("MODE #test +l 2\r\n");
	c.listen();

	c1.command("JOIN #test\r\n");
	c1.listen();

	c2.command("JOIN #test\r\n");
	c2.listen();
}

void Tester::test_mode_channel_m(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	IrcClient c2(_host, _port);
	description("moderated channel");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client1 8 * :Client1 Name\r\n");
	c.command("NICK client1\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client2 8 * :Client2 Name\r\n");
	c1.command("NICK client2\r\n");
	c1.listen(false);

	c2.command("PASS " + _password + "\r\n");
	c2.command("USER client3 8 * :Client3 Name\r\n");
	c2.command("NICK client3\r\n");
	c2.listen(false);

	c.command("JOIN #test\r\n");
	c.listen(false);

	c.command("MODE #test +m\r\n");
	c.listen();

	c1.command("JOIN #test\r\n");
	c1.listen(false);

	c1.command("PRIVMSG #test :trying to speak\r\n");
	c1.listen();

	c.command("MODE #test +o client2\r\n");
	c.listen();

	c1.command("PRIVMSG #test :trying to speak\r\n");
	c1.listen();

	c2.command("JOIN #test\r\n");
	c2.listen(false);

	c.command("MODE #test +v client3\r\n");
	c.listen();

	c2.command("PRIVMSG #test :trying to speak\r\n");
	c2.listen();
}

void Tester::test_mode_channel_n(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	description("no messages to channel from clients on the outside");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client1 8 * :Client1 Name\r\n");
	c.command("NICK client1\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client2 8 * :Client2 Name\r\n");
	c1.command("NICK client2\r\n");
	c1.listen(false);

	c.command("JOIN #test\r\n");
	c.listen(false);

	c.command("MODE #test +n\r\n");
	c.listen();

	c1.command("PRIVMSG #test :trying to speak\r\n");
	c1.listen();

	c.command("MODE #test -n\r\n");
	c.listen();

	c1.command("PRIVMSG #test :trying to speak\r\n");
	c1.listen();
}

void Tester::test_mode_channel_o(void)
{
	IrcClient c(_host, _port);
	IrcClient c1(_host, _port);
	description("give/take channel operator privileges");

	c.command("PASS " + _password + "\r\n");
	c.command("USER client1 8 * :Client1 Name\r\n");
	c.command("NICK client1\r\n");
	c.listen(false);

	c1.command("PASS " + _password + "\r\n");
	c1.command("USER client2 8 * :Client2 Name\r\n");
	c1.command("NICK client2\r\n");
	c1.listen(false);

	c.command("JOIN #test\r\n");
	c.listen(false);

	c1.command("JOIN #test\r\n");
	c1.listen(false);

	c.command("MODE #test +o client2\r\n");
	c.listen();
	
	c1.command("MODE #test -o client1\r\n");
	c1.listen();

	c.command("MODE #test -o client2\r\n");
	c.listen();
}

void Tester::test_mode_channel_t(void)
{
    IrcClient c(_host, _port);
    IrcClient c1(_host, _port);

    description("Set channel topic and check mode");
    c.command("PASS " + _password + "\r\n");
    c.command("USER client1 8 * :Client1 Name\r\n");
    c.command("NICK client1\r\n");
    c.listen(false);
    c1.command("PASS " + _password + "\r\n");
    c1.command("USER client2 8 * :Client2 Name\r\n");
    c1.command("NICK client2\r\n");
    c1.listen(false);
    c.command("MODE #channel +t\r\n");
    c.listen();
    c.command("JOIN #channel\r\n");
    c.listen(false);
    c1.command("JOIN #channel\r\n");
    c.listen(false);
    c1.listen(false);
    c1.command("TOPIC #channel :this is a new topic\r\n");
    c1.listen();
    c.listen();
    c.command("MODE #channel +t\r\n");
    c.listen(false);
    c1.listen(false);
    c1.command("TOPIC #channel :trying to change topic again\r\n");
    c1.listen();
    c.listen(false);
    c.command("TOPIC #channel :Only I can change the topic\r\n");
    c.listen();
    c1.listen(false);
    c.command("MODE #channel -t\r\n");
    c.listen();
    c1.listen(false);
    c1.command("TOPIC #channel :Now I can change topic again\r\n");
    c1.listen();
    c.listen(false);
}

void Tester::test_mode_channel_v(void)
{
    IrcClient c(_host, _port);
    IrcClient c1(_host, _port);

    description("Set channel to moderated and  to channel");
    c.command("PASS " + _password + "\r\n");
    c.command("USER client1 8 * :Client1 Name\r\n");
    c.command("NICK client1\r\n");
    c.listen(false);

    c1.command("PASS " + _password + "\r\n");
    c1.command("USER client2 8 * :Client2 Name\r\n");
    c1.command("NICK client2\r\n");
    c1.listen(false);
    c1.command("JOIN #test1\r\n");
    c1.listen(false);

    c.command("MODE #test1 +v\r\n");
    c.listen();

    c.command("MODE #test1 +v unknown_user\r\n");
    c.listen();

    c.command("MODE #test1 +v client2\r\n");
    c.listen();

    c.command("MODE #test +v\r\n");
    c.listen();

    c.command("MODE #test +v unknown_user\r\n");
    c.listen();

    c.command("MODE #test +v client2\r\n");
    c.listen();

    c.command("JOIN #test\r\n");
    c.listen(false);

    c.command("MODE #test +v\r\n");
    c.listen();

    c.command("MODE #test +v unknown_user\r\n");
    c.listen();

    c.command("MODE #test +v client2\r\n");
    c.listen();
    
    c1.command("JOIN #test\r\n");
    c1.listen();

    c.command("MODE #test +m\r\n");
    c.listen();
    c1.listen();

    c1.command("PRIVMSG #test :trying to speak\r\n");
    c1.listen();

    c.command("MODE #test +v client2\r\n");
    c.listen();
    c1.listen();

    c1.command("PRIVMSG #test :now I can speak\r\n");
    c.listen();
    c1.listen();

    c1.command("MODE #test\r\n");
    c1.listen();

    c1.command("MODE #test -v\r\n");
    c1.listen();

    c1.command("MODE #test -m\r\n");
    c1.listen();

    c.command("MODE #test -v client2\r\n");
    c.listen();
    c1.listen();

    c1.command("PRIVMSG #test :trying to speak\r\n");
    c1.listen();

    c.command("MODE #test -m\r\n");
    c.listen();
    c1.listen();

    c1.command("PRIVMSG #test :now I can speak\r\n");
    c1.listen();
}

void Tester::test_mode_channel_k(void)
{
    IrcClient c(_host, _port);
    IrcClient c1(_host, _port);

    description("Set the user key to channel");
    c.command("PASS " + _password + "\r\n");
    c.command("USER client1 8 * :Client1 Name\r\n");
    c.command("NICK client1\r\n");
    c.listen(false);

    c1.command("PASS " + _password + "\r\n");
    c1.command("USER client2 8 * :Client2 Name\r\n");
    c1.command("NICK client2\r\n");
    c1.listen(false);
    c1.command("JOIN #test1\r\n");
    c1.listen(false);

    c.command("MODE #test +k pass\r\n");
    c.listen();

    c.command("MODE #test1 +k pass\r\n");
    c.listen();

    c.command("JOIN #test\r\n");
    c.listen(false);

    c.command("MODE\r\n");
    c.listen();

    c.command("MODE #test\r\n");
    c.listen();

    c.command("MODE #test +k\r\n");
    c.listen();

    c.command("MODE #test +k pass\r\n");
    c.listen();

    c.command("MODE #test\r\n");
    c.listen();

    c1.command("JOIN #test\r\n");
    c1.listen();

    c1.command("JOIN #test wrong_pass\r\n");
    c1.listen();

    c1.command("JOIN #test pass\r\n");
    c1.listen();

    c1.command("PART #test\r\n");
    c1.listen();
    c.listen(false);

    c1.command("JOIN #test\r\n");
    c1.listen();

    c.command("MODE #test -k\r\n");
    c.listen();

    c.command("MODE #test -k wrong_pass\r\n");
    c.listen();

    c.command("MODE #test -k pass\r\n");
    c.listen();

    c1.command("JOIN #test\r\n");
    c1.listen();

    c.command("MODE #test +k pass\r\n");
    c.listen();
    c1.listen();

    c1.command("MODE #test -k pass\r\n");
    c1.listen();

    c1.command("MODE #test +k pass\r\n");
    c1.listen();

    c1.command("MODE #test +k\r\n");
    c1.listen();
}

void Tester::test_mode_channel(void)
{
	title("mode_channel");
	test_mode_channel_b();
	test_mode_channel_i();
	test_mode_channel_m();
	test_mode_channel_n();
	test_mode_channel_o();
	test_mode_channel_v();
	test_mode_channel_k();
}
