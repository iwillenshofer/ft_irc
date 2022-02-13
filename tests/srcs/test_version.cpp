/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_version.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:07:25 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/12 20:55:03 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

void Tester::test_version(void)
{
	std::string nick;
	IrcClient c(_host, _port);

	title("version");
	description("Tests version without parameters, with wrong servername and with correct server name");
	c.command("PASS " + _password + "\r\n");
	c.command("USER client 8 * :Client Name\r\n");
	c.command("NICK client\r\n");
	c.listen(false);
	c.command("VERSION unknown_server\r\n");
	c.listen();
	c.command("VERSION irc.42network.com\r\n");
	c.listen();
	c.command("VERSION\r\n");
	c.listen();
}
