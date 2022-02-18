/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:20:32 by roman             #+#    #+#             */
/*   Updated: 2022/02/18 20:26:30 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

Tester::Tester(std::string host, int port, std::string password): _host(host), _port(port), _password(password)
{
	feed_prompt();
	loop();
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

/*
** Command Prompt functions
*/

void Tester::feed_prompt(void)
{
	std::map<std::string, cmd_type> tmp;

	tmp["Password"] = &Tester::test_pass;
	tmp["Nickname"] = &Tester::test_nick;
	tmp["User"] = &Tester::test_user;
	tmp["Server"] = &Tester::test_server;
	tmp["Operator"] = &Tester::test_oper;
	tmp["Quit"] = &Tester::test_quit;
	tmp["Server Quit"] = &Tester::test_squit;
	_map["Connection Registration"] = tmp;
	tmp.clear();
	tmp["Join"] = &Tester::test_join;
	tmp["Part"] = &Tester::test_part;
	tmp["Channel modes"] = &Tester::test_mode_channel;
	tmp["User modes"] = &Tester::test_mode_user;
	tmp["Topic"] = &Tester::test_topic;
	tmp["Names"] = 	&Tester::test_names;
	tmp["List"] = &Tester::test_list;
	tmp["Invite"] = &Tester::test_invite;
	tmp["Kick"] = &Tester::test_kick;
	_map["Channel operations"] = tmp;
	tmp.clear();
	tmp["Version"] = &Tester::test_version;
	tmp["Stats"] = &Tester::test_stats;
	tmp["Links"] = &Tester::test_links;
	tmp["Time"] = &Tester::test_time;
	tmp["Connect"] = &Tester::test_connect;
	tmp["Trace"] = &Tester::test_trace;
	tmp["Admin"] = &Tester::test_admin;
	tmp["Info"] = &Tester::test_info;
	tmp["Lusers"] = &Tester::test_admin;
	tmp["Motd"] = &Tester::test_motd;
	_map["Server queries and commands"] = tmp;
	tmp.clear();
	tmp["Private messages"] = &Tester::test_privmsg;
	tmp["Notice messages"] = &Tester::test_notice;
	_map["Sending messages"] = tmp;
	tmp.clear();
	tmp["Who query"] = &Tester::test_who;
	tmp["Whois query"] = &Tester::test_whois;
	tmp["Whowas"] = &Tester::test_whowas;
	_map["User-based queries"] = tmp;
	tmp.clear();
	tmp["Kill"] = &Tester::test_kill;
	tmp["Ping"] = &Tester::test_ping;
	tmp["Pong"] = &Tester::test_pong;
	tmp["Error"] = &Tester::test_error;
	_map["Miscellaneous messages"] = tmp;
	tmp.clear();
	tmp["Away"] = &Tester::test_away;
	tmp["Registration"] = &Tester::test_registration;
	_map["Optional/Others"] = tmp;
}


void Tester::prompt_menu_title(std::string s, bool center)
{
	std::string str;

	if (center)
	{
		ft::uppercase(s);
		while (s.size() < MENU_WIDTH)
			s = " " + s + " ";
		if (s.size() > MENU_WIDTH)
			s.erase(0, 1);
	}
	str += std::string("\033[");
	str += ft::to_string(CLR_BOLD) +  ";";
	str += ft::to_string(CLR_BLUE) + "m";
	std::cout << str << s << std::string("\033[0m") << std::endl;
}

void Tester::prompt_menu_item(std::string choice, std::string description)
{
	std::string str;

	str += std::string("\033[");
	str += ft::to_string(CLR_BOLD) +  ";";
	if (choice == "A")
		str += ft::to_string(CLR_GREEN) + "m";
	else if (choice == "B")
		str += ft::to_string(CLR_YELLOW) + "m";
	else if (choice == "E")
		str += ft::to_string(CLR_RED) + "m";
	else
		str += ft::to_string(CLR_CYAN) + "m";
	std::cout << str << choice << std::string("\033[37m") <<  "  - " << description  << std::string("\033[0m")<<  std::endl;
}

Tester::sub_map_type *Tester::_get_submap(int level)
{
	map_iterator mit = _map.begin();
	for (int j = 0; j < level && mit != _map.end(); j++)
		mit++;
	if (mit == _map.end())
		return NULL;
	return (&(mit->second));
}


void Tester::_clear_screen()
{
	std::cout << "\033[2J" << std::endl;
	std::cout << "\033[H" << std::endl;

}
void Tester::prompt(int level, bool error, bool clear)
{
	int i = 1;
	sub_map_type *smap;

	if (clear)
		_clear_screen();
	if (!level)
	{
		prompt_menu_title("--- Main Menu ---", true);
		for (map_iterator it = _map.begin(); it != _map.end(); it++, i++)
			prompt_menu_item(std::to_string(i), it->first);	}
	else
	{
		prompt_menu_title("--- Commands ---", true);
		smap = _get_submap(level - 1);
		for (sub_map_iterator it = smap->begin(); it != smap->end(); it++, i++)
			prompt_menu_item(std::to_string(i), it->first);
	}
	prompt_menu_item("A", "All");
	if (level)
		prompt_menu_item("B", "Back");
	prompt_menu_item("E", "Exit");
	if (error)
		std::cout << "\033[1;31m*  *  * Invalid Command *  *  *\033[0m" << std::endl;
	std::cout << ": ";
}

void Tester::_run_command(size_t level, size_t command)
{
	sub_map_type *smap = _get_submap(--level);
	sub_map_iterator sit = smap->begin();

	for (size_t i = 0; i < command - 1; i++)
		sit++;
	(*this.*(sit->second))();
}

void Tester::_run_all_commands(size_t level)
{
	sub_map_type *smap = NULL;

	if (!level)
	{
		for (map_iterator it = _map.begin(); it != _map.end(); it++)
			for (sub_map_iterator sit = it->second.begin(); sit != it->second.end(); sit++)
				(*this.*(sit->second))();
	}
	else
	{
		smap = _get_submap(--level);
		for (sub_map_iterator sit = smap->begin(); sit != smap->end(); sit++)
			(*this.*(sit->second))();
	}
}


void Tester::loop(void)
{
	std::string	command;
	bool 		error = false;
	size_t		level = 0;
	size_t		nb = 0;
	bool		clear = true;

	while (1)
	{
		prompt(level, error, clear);
		error = false;
		clear = true;
		command.clear();
		std::cin >> command;
		nb = std::atoi(command.c_str());
		if ((command.size() > 1 && !(ft::is_numeric(command)))
			|| (!nb && command != "E" && command != "A" && command != "B")
			|| (!level && command == "B")
			|| (!level && nb && nb > _map.size())
			|| (level && nb && nb > (_get_submap(level - 1)->size())))
		{
			error = true;
			continue ;
		}
		if (command == "E")
			break;
		else if (command == "B")
			level = 0;
		else if (command == "A")
		{
			_run_all_commands(level);
			clear = false;
		}
		else if (!level)
			level = nb;
		else
		{
			_run_command(level, nb);
			clear = false;
		}
	}
}

void Tester::perform_tests(void)
{
	test_pass();
	test_nick();
	test_user();
	test_server();
	test_oper();
	test_quit();
	test_squit();
	test_join();
	test_part();
	test_mode_channel();
	test_mode_user();
	test_topic();
	test_admin();
	test_connect();
	test_error();
	test_info();
	test_list();
	test_names();
	test_kick();
	test_invite();
	test_kill();
	test_links();
	test_notice();
	test_privmsg();
	test_who();
	test_whois();
	test_whowas();
	test_ping();
	test_pong();
	test_stats();
	test_time();
	test_trace();
	test_version();
	test_lusers();
	test_motd();
	test_registration();
}
