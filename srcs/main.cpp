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

int main (int argc, char **argv)
{
	Debug::setLevel(DBG_DEV);
	try
	{
		if (argc == 1)
		{
			WebServer p;
		}
		else if (argc == 2)
		{
			WebServer p(194);
		}
		else
			throw std::runtime_error("Invalid number of arguments");
	}
	catch(const std::runtime_error& e)
	{
		Debug(std::string(e.what()));
		return (1);
	}
	(void)(argv);
}
