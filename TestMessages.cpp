/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestMessages.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:02:08 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/20 20:56:20 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/Message.hpp"
#include <string>
#include <iostream>

# define LINE_SIZE 20

void title(std::string s)
{
	ft::uppercase(s);
	s = "* * * " + s + " * * *";
	while (s.size() < LINE_SIZE)
		s = " " + s + " ";
	if (s.size() > LINE_SIZE)
		s.pop_back();
	std::cout << std::endl << "\x1B[1;30;47m" << s << "\033[0m" << std::endl;
}

void check(bool(*fn)(const std::string &), std::string s)
{
    bool result = fn(s);
	if (s.empty())
		s = "EMPTY";
    std::cout << (result ? "\x1B[1;32m" : "\x1B[1;31m") << s << "\033[0m" << std::endl;
}

int main (void)
{
	title("channel");
	check(Message::is_bnf_channel, "");
	check(Message::is_bnf_channel, "#channel");
	check(Message::is_bnf_channel, "#aaaaaaaaaaaaaa");
	check(Message::is_bnf_channel, "+aaaaaaaaaa");
	check(Message::is_bnf_channel, "&aaaaaaaaaa");
	check(Message::is_bnf_channel, "!aaaaaaaaaa");
	check(Message::is_bnf_channel, "!AAAAAaaaa");
	check(Message::is_bnf_channel, "!");
	check(Message::is_bnf_channel, "@");
	check(Message::is_bnf_channel, "#");
	check(Message::is_bnf_channel, "a");
	check(Message::is_bnf_channel, "#a");
	check(Message::is_bnf_channel, "zzzzzz");
	check(Message::is_bnf_channel, "#");
	check(Message::is_bnf_channel, "#zzzzçzz");
	check(Message::is_bnf_channel, "#aaa.aaa");
	check(Message::is_bnf_channel, "#aaa:aaa");
	check(Message::is_bnf_channel, "#aaa,aaa");
	check(Message::is_bnf_channel, "#aaa aaa");
	check(Message::is_bnf_channel, "#[aaa]");
	check(Message::is_bnf_channel, "#[a#aa]");

	title("nickname");
	check(Message::is_bnf_nickname, "");
	check(Message::is_bnf_nickname, "#channel");
	check(Message::is_bnf_nickname, "#aaaaaaaaaaaaaa");
	check(Message::is_bnf_nickname, "+aaaaaaaaaa");
	check(Message::is_bnf_nickname, "&aaaaaaaaaa");
	check(Message::is_bnf_nickname, "!aaaaaaaaaa");
	check(Message::is_bnf_nickname, "!AAAAAaaaa");
	check(Message::is_bnf_nickname, "!");
	check(Message::is_bnf_nickname, "@");
	check(Message::is_bnf_nickname, "#");
	check(Message::is_bnf_nickname, "a");
	check(Message::is_bnf_nickname, "#a");
	check(Message::is_bnf_nickname, "zzzzzz");
	check(Message::is_bnf_nickname, "#");
	check(Message::is_bnf_nickname, "#zzzzçzz");
	check(Message::is_bnf_nickname, "aaa.aaa");
	check(Message::is_bnf_nickname, "aaa:aaa");
	check(Message::is_bnf_nickname, "aaa,aaa");
	check(Message::is_bnf_nickname, "aaa aaa");
	check(Message::is_bnf_nickname, "[aaa]");
	check(Message::is_bnf_nickname, "[a#aa]");
	check(Message::is_bnf_nickname, "iwillens");
	check(Message::is_bnf_nickname, "iwillens3");
	check(Message::is_bnf_nickname, "iwillçens3");
	check(Message::is_bnf_nickname, "3iwillens");
	check(Message::is_bnf_nickname, "-hello");
	check(Message::is_bnf_nickname, "hello-");
	check(Message::is_bnf_nickname, "[]\\`_{|}");
	check(Message::is_bnf_nickname, "[]\\`_{|}-");
	check(Message::is_bnf_nickname, "[]\\`_^|}-123456789");



	title("host");
	check(Message::is_bnf_host, "");
	check(Message::is_bnf_host, "255.255.255.255");
	check(Message::is_bnf_host, "0.0.0.0");
	check(Message::is_bnf_host, "127.0.0.1");
	check(Message::is_bnf_host, "a.b.c.d");
	check(Message::is_bnf_host, "127001");
	check(Message::is_bnf_host, "-127001");
	check(Message::is_bnf_host, "127001-");
	check(Message::is_bnf_host, "127..0..0..1");
	check(Message::is_bnf_host, "helloworld");
	check(Message::is_bnf_host, "0.*");
	check(Message::is_bnf_host, "0:0:0:0:0:0:255.255.255.255");
	check(Message::is_bnf_host, "google.com");
	check(Message::is_bnf_host, "42sp.org.br");
	check(Message::is_bnf_host, ".google.com");
	check(Message::is_bnf_host, "42sp.org.");
	check(Message::is_bnf_host, "*.42sp.org.br");

//	title("others");
//	check(Message::is_bnf_target, "");
//	check(Message::is_bnf_msgtarget, "");
//	check(Message::is_bnf_msgto, "");
//	check(Message::is_bnf_channel, "");
//	check(Message::is_bnf_servername, "");
//	check(Message::is_bnf_hostname, "");
//	check(Message::is_bnf_shortname, "");
//	check(Message::is_bnf_hostaddr, "");
//	check(Message::is_bnf_ipv4addr, "");
//	check(Message::is_bnf_ipv6addr, "");
//	check(Message::is_bnf_nickname, "");
//	check(Message::is_bnf_targetmask, "");
//	check(Message::is_bnf_chanstring, "");
//	check(Message::is_bnf_channelid, "");
//	check(Message::is_bnf_user, "");
//	check(Message::is_bnf_key, "");
//
    std::cout << std::endl;
	return 1 ;
}


















