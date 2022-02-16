/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_motd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:21:19 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 21:38:05 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_motd(void)
{
	IrcClient c(_host, _port);

	title("motd");
	description("Testing message of the day");
	c.command("PASS " + _password + "\r\n", false);
	c.command("NICK client\r\n", false);
	c.command("USER username hostname servername realname\r\n", false);
	c.listen(false);
	c.command("MOTD\r\n");
	c.listen();
}

