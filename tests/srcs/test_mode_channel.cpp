/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mode_channel.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:14 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/17 18:29:55 by roman            ###   ########.fr       */
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
	title("mode_channel");

}

void Tester::test_mode_channel_n(void)
{
	title("mode_channel");

}

void Tester::test_mode_channel_o(void)
{
	title("mode_channel");

}

void Tester::test_mode_channel_p(void)
{
	title("mode_channel");

}

void Tester::test_mode_channel_s(void)
{
	title("mode_channel");

}

void Tester::test_mode_channel_t(void)
{
	title("mode_channel");

}

void Tester::test_mode_channel_v(void)
{
	title("mode_channel");

}

void Tester::test_mode_channel_k(void)
{
	title("mode_channel");

}

void Tester::test_mode_channel(void)
{
	title("mode_channel");
	//test_mode_channel_b();
	test_mode_channel_i();
}
