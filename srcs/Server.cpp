/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:38:51 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/24 22:22:53 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(std::string host, std::string password)
:_version(SRV_VERSION), _servername(host), _password(password), _motdfilename(SRV_MOTD_FILE), _highest_connections(0)
{
	_init();
}

Server::Server(Server const &cp) { *this = cp; }
Server &Server::operator=(Server const &cp)
{
	_version = cp._version;
	_password = cp._password;
	_servername = cp._servername;
	_operators = cp._operators;
	_motdfilename = cp._motdfilename;
	_whowaslist = cp._whowaslist;
	return (*this);
}

Server::~Server(void) { }

void Server::_init(void)
{
	_operators.insert(std::make_pair("iwillens", "senha1"));
	_operators.insert(std::make_pair("robitett", "senha1"));
	std::time(&_creation_date);
}

/*
** getters
*/
std::string							&Server::password(void) { return (_password); }
std::string							&Server::version(void) { return (_version); }
std::string							&Server::servername(void) { return (_servername); }
std::map<std::string, std::string>	&Server::operators(void) { return (_operators); }
std::string							&Server::motdfilename(void) { return (_motdfilename); }

void								Server::add_whowas(Client &client)
{ 
	_whowaslist[client.nickname].insert(_whowaslist[client.nickname].begin(), client);
}
std::map<std::string, std::vector<Client> >	&Server::whowas(void) { return (_whowaslist); }
size_t								Server::highest_connections(void) { return (_highest_connections); }
size_t								Server::highest_connections(size_t current_connections)
{
	if (current_connections > _highest_connections)
		_highest_connections = current_connections;
	return (_highest_connections);
}

time_t								&Server::creation_date(void) { return (_creation_date); }
std::string							Server::formatted_creation_date(void) { return (ft::format_date(_creation_date)); }	
