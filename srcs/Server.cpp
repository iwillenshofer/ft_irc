/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:38:51 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/17 22:41:29 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(std::string host, unsigned long password)
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
	_cmd_stats = cp._cmd_stats;
	return (*this);
}

Server::~Server(void) { }

/*
** OPER passwords
** iwillens: Igor123
** roman: Roman123
*/
void Server::_init(void)
{
	_operators.insert(std::make_pair("iwillens", 229428285555564));
	_operators.insert(std::make_pair("robitett", 7571527224823800));
	std::time(&_creation_date);
}

/*
** getters
*/
unsigned long							&Server::password(void) { return (_password); }
std::string								&Server::version(void) { return (_version); }
std::string								&Server::servername(void) { return (_servername); }
std::map<std::string, unsigned long>	&Server::operators(void) { return (_operators); }
std::string								&Server::motdfilename(void) { return (_motdfilename); }

void								Server::add_whowas(Client &client)
{ 
	_whowaslist[client.nickname].insert(_whowaslist[client.nickname].begin(), client);
}

std::map<std::string, std::vector<Client> >	&Server::whowas(void) { return (_whowaslist); }
std::map<std::string, size_t >				&Server::commandstats(void) { return (_cmd_stats); }
size_t								Server::highest_connections(void) { return (_highest_connections); }
size_t								Server::highest_connections(size_t current_connections)
{
	if (current_connections > _highest_connections)
		_highest_connections = current_connections;
	return (_highest_connections);
}

time_t								&Server::creation_date(void) { return (_creation_date); }
std::string							Server::formatted_creation_date(void) { return (ft::format_date(_creation_date)); }	
