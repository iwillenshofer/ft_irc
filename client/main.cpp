/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 11:37:22 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/21 21:00:10 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcClient.hpp"
#include <pthread.h>
#include <iostream>
#include <csignal>
#include <signal.h>

#define THREAD_SIZE 500

typedef struct s_args
{
	std::string host;
	int			port;
	std::string	password;
} t_args;

void *startClient(void *args)
{
	std::string host = (static_cast<t_args *>(args))->host;
	int port = (static_cast<t_args *>(args))->port;
	std::string password = (static_cast<t_args *>(args))->password;
	try
	{
		Debug("Starting: " + host + " " + ft::to_string(port) + " " + password, DBG_INFO);
		IrcClient p;
		p.create_socket();
		p.connect_socket(host, port, password);
		p.runClient();
		Debug("Client successfully shut down.", DBG_INFO);
	}
	catch(const std::runtime_error& e)
	{
		Debug(std::string(e.what()), DBG_FATAL);
	}
	return NULL;
}

int main(int argc, char **argv)
{
	t_args		args;
	int 		quantity;

	if (argc < 4)
	{
		Debug("USAGE: ./irclient <host> <port> <password> [clients = 30].", DBG_FATAL);
		return (1) ;
	}
	args.host = std::string(argv[1]);
	args.port = std::atoi(argv[2]);
	args.password = std::string(argv[3]);
	if (argc > 4)
		quantity = std::atoi(argv[4]);
	else
		quantity = 30;
	pthread_t	*threads = new pthread_t[quantity];
	for (int i = 0; i < quantity; i++)
		pthread_create( &(threads[i]), NULL, startClient, (void*)&args);
	for (int i = 0; i < quantity; i++)
		pthread_join(threads[i], NULL);
	delete [] threads;
	return 0;
}
