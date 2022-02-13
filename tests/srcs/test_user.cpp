/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_user.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:07:22 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/12 21:15:09 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_user_parameters(void)
{
	std::string nick;
	IrcClient c(_host, _port);

	description("Testing parameters and re-registering user.");
	c.command("PASS " + _password + "\r\n");
	c.command("NICK client\r\n");
	c.command("USER\r\n");
	c.listen();
	c.command("USER username\r\n");
	c.listen();
	c.command("USER username hostname\r\n");
	c.listen();
	c.command("USER username hostname servername\r\n");
	c.listen();
	c.command("USER username hostname servername realname\r\n");
	c.listen();
	c.command("USER username hostname servername\r\n");
	c.listen();
}

void Tester::test_user(void)
{
	title("user");
	test_user_parameters();
}
