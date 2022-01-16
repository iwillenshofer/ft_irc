/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:48:00 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/09 12:12:09 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "WebServer.hpp"
#include <unistd.h>

bool	check_port(std::string port)
{
	for (std::string::iterator it = port.begin(); it != port.end(); it++)
	{
		if (isdigit(*it) == 0)
			return false;
	}
	int port_int = atoi(port.c_str());
	if (port_int < 0 || port_int > 65536)
		return false;
	return true;
}

bool	check_password(std::string password)
{
	for (std::string::iterator it = password.begin(); it != password.end(); it++)
	{
		if (isprint(*it) == 0)
			return false;
	}
	return true;
}

std::vector<std::string>	parse_args(int argc, char **argv)
{
	std::vector<std::string> args;

	if (argc == 2)
	{
		args.push_back(argv[0]);
		args.push_back(argv[1]);
	}
	else if (argc == 3)
	{
		args.push_back(argv[1]);
		args.push_back(argv[2]);
	}
	else
	{
		throw std::runtime_error("Invalid number of arguments");
	}
	if (check_port(args.at(0)) == false)
		throw std::runtime_error("Invalid port number");
	if (check_password(args.at(1)) == false)
		throw std::runtime_error("Invalid password format");
	return args;
}

int main (int argc, char **argv)
{
	Debug::setLevel(DBG_DEV);

	try
	{
		std::vector<std::string> args = parse_args(argc - 1, argv + 1);
		WebServer p(atoi(args.at(0).c_str()));
	}
	catch(const std::runtime_error& e)
	{
		Debug(std::string(e.what()));
		return (1);
	}
}
