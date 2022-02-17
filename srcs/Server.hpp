/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:38:48 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/17 21:28:09 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <map>
# include "Debug.hpp"
# include "Client.hpp"
# include "server_defaults.hpp"

/*
** Server Properties
*/
class Client;

class Server
{
	public:
		Server(std::string host = SRV_SERVERNAME, unsigned long password = 0);
		Server(Server const &cp);
		Server &operator=(Server const &cp);
		virtual ~Server();
	
	
	private:
		std::string										_version;
		std::string										_servername;
		unsigned long									_password;
		std::map<std::string, unsigned long>			_operators;
		std::string										_motdfilename;
		std::map<std::string, std::vector<Client> >		_whowaslist;
		size_t											_highest_connections;
		time_t											_creation_date;
		std::map<std::string, size_t>					_cmd_stats;

		void _init(void);

	public:
		/*
		** getters
		*/
		unsigned long							&password(void);
		std::string								&version(void);
		std::string								&servername(void);
		std::map<std::string, unsigned long>	&operators(void);
		std::string								&motdfilename(void);

		void										add_whowas(Client &client);
		std::map<std::string, std::vector<Client> >	&whowas(void);
		std::map<std::string, size_t >				&commandstats(void);
		size_t										highest_connections(void);
		size_t										highest_connections(size_t current_connections);

		time_t										&creation_date(void);
		std::string									formatted_creation_date(void);
};

#endif
