/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:38:48 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/26 00:21:08 by iwillens         ###   ########.fr       */
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
		Server(std::string host = SRV_SERVERNAME, std::string password = "");
		
		Server(Server const &cp);
		Server &operator=(Server const &cp);
		virtual ~Server();
	
	
	private:
		std::string								_version;
		std::string								_servername;
		std::string								_password;
		std::map<std::string, std::string>		_operators;
		std::string								_motdfilename;
		std::map<std::string, std::vector<Client> >		_whowaslist;
		size_t									_highest_connections;
		time_t									_creation_date;

		void _init(void);

	public:
		/*
		** getters
		*/
		std::string							&password(void);
		std::string							&version(void);
		std::string							&servername(void);
		std::map<std::string, std::string>	&operators(void);
		std::string							&motdfilename(void);

		void								add_whowas(Client &client);
		std::map<std::string, std::vector<Client> >	&whowas(void);
		size_t								highest_connections(void);
		size_t								highest_connections(size_t current_connections);

		time_t								&creation_date(void);
		std::string							formatted_creation_date(void);
};

#endif
