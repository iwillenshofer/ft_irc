/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:38:48 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/21 12:41:01 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <map>
# include "Debug.hpp"
# include "server_defaults.hpp"

/*
** Server Properties
*/

typedef struct s_userattr
{
		std::string 	username;
		std::string 	hostname;
		std::string 	realname;
		time_t			joined_time;
} t_userattr;

class Server
{
	public:
		Server(void):_version(SRV_VERSION), _servername(SRV_SERVERNAME), _motdfilename(SRV_MOTD_FILE), _highest_connections(0) { _init(); };
		Server(Server const &cp) { *this = cp; }
		Server &operator=(Server const &cp)
		{
			_version = cp._version;
			_servername = cp._servername;
			_operators = cp._operators;
			_motdfilename = cp._motdfilename;
			_whowaslist = cp._whowaslist;
			return (*this);
		}
		virtual ~Server() { };
	
	
	private:
		std::string								_version;
		std::string								_servername;
		std::map<std::string, std::string>		_operators;
		std::string								_motdfilename;
		std::multimap<std::string, t_userattr>	_whowaslist;
		size_t									_highest_connections;
		time_t									_creation_date;

		void _init(void)
		{
			_operators.insert(std::make_pair("iwillens", "senha1"));
			_operators.insert(std::make_pair("robitett", "senha1"));
			std::time(&_creation_date);
		}

	public:
		/*
		** getters
		*/
		std::string							&version(void) { return (_version); }
		std::string							&servername(void) { return (_servername); }
		std::map<std::string, std::string>	&operators(void) { return (_operators); }
		std::string							&motdfilename(void) { return (_motdfilename); }
		std::vector<std::string>			whowaslist(std::string &s)
		{ 
			//todo
			std::vector<std::string> list;
			(void)(s);
			return (list);
		}
		size_t								highest_connections(void) { return (_highest_connections); }
		size_t								highest_connections(size_t current_connections)
		{
			if (current_connections > _highest_connections)
				_highest_connections = current_connections;
			return (_highest_connections);
		}

		time_t								&creation_date(void) { return (_creation_date); }
		std::string							formatted_creation_date(void) { return (ft::format_date(_creation_date)); }	
};

#endif
