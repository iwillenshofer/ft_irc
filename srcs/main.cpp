/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:48:00 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/31 14:07:47 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "IrcServer.hpp"
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

bool	check_optional(char *optional, std::string &host)
{
	std::string str = optional;
	std::stringstream ss(str);
	std::string token;
	std::vector<std::string> vector_args;

	while (std::getline(ss, token, ':'))
		vector_args.push_back(token);
	if (std::count(str.begin(), str.end(), ':') != 2)
		return false;
	for (std::string::iterator it = vector_args.at(0).begin(); it != vector_args.at(0).end(); it++)
	{
		if (isprint(*it) == 0)
			return false;
	}
	host = vector_args.at(0);
	if (host.empty())
		host = "*";
	return true;
}

std::vector<std::string>	parse_args(int argc, char **argv)
{
	std::vector<std::string> args;
	std::string host;

	if (argc == 2)
	{
		args.push_back(SRV_SERVERNAME);
		args.push_back(argv[0]);
		args.push_back(argv[1]);
	}
	else if (argc == 3)
	{
		if (check_optional(argv[0], host) == false)
			throw std::runtime_error("Invalid optional argument");
		args.push_back(host);
		args.push_back(argv[1]);
		args.push_back(argv[2]);
	}
	else
	{
		throw std::runtime_error("Invalid number of arguments");
	}
	if (check_port(args.at(1)) == false)
		throw std::runtime_error("Invalid port number");
	if (check_password(args.at(2)) == false)
		throw std::runtime_error("Invalid password format");
	return args;
}

int main (int argc, char **argv)
{
	Debug::set_level(DBG_DEV);

	try
	{
		std::vector<std::string> args = parse_args(argc - 1, argv + 1);
		IrcServer p(args.at(0), atoi(args.at(1).c_str()), args.at(2));
		Debug("Server successfully shut down.", DBG_INFO);
	}
	catch(const std::runtime_error& e)
	{
		Debug(std::string(e.what()), DBG_FATAL);
		return (1);
	}
}
