/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 11:37:22 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/17 16:08:48 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.hpp"

int main(int argc, char **argv)
{
	int port;
	std::string host;
	std::string pass;

	if (argc < 4)
	{
		Debug(std::string("USAGE: ") + argv[0] + " <host> <port> <password>", DBG_FATAL);
		return (1) ;
	}
	host = std::string(argv[1]);
	port = std::atoi(argv[2]);
	pass = std::string(argv[3]);
	Debug::set_level(DBG_DEV);
	try
	{
		Tester t(host, port, pass);
	}
	catch(const std::runtime_error& e)
	{
		Debug(std::string(e.what()), DBG_FATAL);
	}


    return 0;
}
