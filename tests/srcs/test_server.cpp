/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:50 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 20:05:39 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_server(void)
{
	IrcClient c(_host, _port);

	title("server");
	description("Testing server command");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("SERVER\r\n");
	c.listen();
	c.command("SERVER servername\r\n");
	c.listen();
	c.command("SERVER servername hopcount\r\n");
	c.listen();
	c.command("SERVER servername hopcount info\r\n");
	c.listen();
}
