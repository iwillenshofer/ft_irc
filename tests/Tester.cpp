/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 20:53:03 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/15 21:53:22 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

Tester::Tester(std::string host, int port, std::string password): _host(host), _port(port), _password(password)
{
	perform_tests();
}

Tester::Tester(Tester const &cp) { *this = cp; };
Tester &Tester::operator=(Tester const &cp)
{
	_host = cp._host;
	_port = cp._port;
	_password = cp._password;
	return (*this);
}
Tester::~Tester() {};

std::vector<std::string> Tester::_break_line(std::string s)
{
	std::vector<std::string> v;
	std::string tmp;
	size_t pos;
	int i = 0;

	while (s.size())
	{
		tmp = s.substr(0, LINE_WIDTH - 3);
		pos = tmp.find_last_of(' ');
		if (pos >= LINE_WIDTH - 3 && pos != std::string::npos)
			tmp = tmp.substr(0, pos);
		s = s.substr(tmp.size());
		if (tmp.size() && tmp[0] == ' ')
			tmp.erase(0, 1);
		v.push_back(tmp);
		i++;
	}
	return (v);
}

void Tester::title(std::string s)
{
	std::string str;

	ft::uppercase(s);
	s = "- " + s + " -";
	while (s.size() < LINE_WIDTH)
		s = " " + s + " ";
	if (s.size() > LINE_WIDTH)
		s.erase(0, 1);
	str += std::string("\033[");
	str += ft::to_string(0) +  ";";
	str += ft::to_string(CLR_BLACK) +  ";";
	str += ft::to_string(46) + "m";
	std::cout << std::endl << str << s << std::string("\033[0m") << std::endl;
}

void Tester::description(std::string s)
{
	std::string str;
	std::vector<std::string> v = _break_line(s);

	str += std::string("\033[");
	str += ft::to_string(CLR_ITALICS) +  ";";
	str += ft::to_string(CLR_BLACK) +  ";";
	str += ft::to_string(90) + "m";
	std::cout << str << "/*"<< std::endl;
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << "** " << *it << std::endl;
	std::cout << std::string("*/\033[0m") << std::endl;	
}

void Tester::perform_tests(void)
{
//	test_registration();
//	test_admin();
//	test_connect();
//	test_error();
//	test_info();
//	test_invite();
//	test_join();
//	test_kick();
//	test_kill();
//	test_links();
//	test_list();
//	test_lusers();
//	test_mode_channel();
//	test_mode_user();
//	test_motd();
//	test_names();
//	test_nick();
//	test_notice();
//	test_oper();
	test_part();
//	test_pass();
//	test_ping();
//	test_pong();
//	test_privmsg();
//	test_quit();
//	test_server();
//	test_squit();
//	test_stats();
//	test_time();
//	test_topic();
//	test_trace();
//	test_user();
//	test_version();
//	test_who();
//	test_whois();
//	test_whowas();
}
