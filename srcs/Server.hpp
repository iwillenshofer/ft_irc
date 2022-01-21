/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:38:48 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/20 21:58:46 by iwillens         ###   ########.fr       */
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

class Server
{
	public:
		Server(void):_version(SRV_VERSION), _servername(SRV_SERVERNAME) { };
		Server(Server const &cp) { *this = cp; }
		Server &operator=(Server const &cp)
		{
			_version = cp._version;
			return (*this);
		}
		virtual ~Server() { };
	
	
	private:
		std::string							_version;
		std::string							_servername;
		std::map<std::string, std::string>	_operators;
		std::string							_motdfilename;

	public:
		/*
		** getters
		*/
		std::string							&version(void) { return (_version); }
		std::string							&servername(void) { return (_servername); }
		std::map<std::string, std::string>	&operators(void) { return (_operators); }
		std::string							&motdfilename(void) { return (_motdfilename); }

};

#endif
