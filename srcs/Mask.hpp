/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mask.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:05:44 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/23 14:48:15 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MASK_HPP
# define MASK_HPP

# include <string>
# include <vector>
# include <algorithm>
# include "Debug.hpp"
# include "Client.hpp"
# include "server_defaults.hpp"

/*
** Goals of this class:
** 1. Match a nickname or user (full prefix) against a mask
** 2. generate a mask upon entering a nickname or a user
**
** A target format is <nickname> [!<username>] [@<hostname>]
** Usage:
** Mask::match(nickname, mask);
** Mask::match(client, mask);
** Mask::match("nickname!user@hostname", mask);
** Mask::create("nickname"); nickname!*@*
*/

class Client;

class Mask
{
	public:
		Mask(void);
		Mask(Mask const &cp);
		Mask &operator=(Mask const &cp);
		virtual ~Mask();
	
		class Maskparts
		{
			public:
				Maskparts(void);
				Maskparts(std::string s);
				Maskparts(Maskparts const &cp);
				Maskparts &operator=(Maskparts const &cp);
				virtual ~Maskparts();
				std::string nickname;
				std::string username;
				std::string hostname;
				std::string fullmask( void );
			private:
				static std::string _striphost(std::string &string);
				static std::string _stripuser(std::string &string);

				void _strip(std::string string);
		};

	private:

		static bool	_match(std::string::iterator target, std::string::iterator mask, std::string::iterator t_end, std::string::iterator m_end);

	public:
		/*
		** getters
		*/
		static bool	match(Client &client, std::string mask);
		static bool	match(std::string target, std::string mask);

		static bool	match(Maskparts &target, Maskparts &mask);
		/*
		** match raw:
		** matches a string against a mask without parsing it into username, nickname
		** and hostname 
		*/
		static bool	match_raw(std::string target, std::string mask);

		static std::string create(std::string target);
};

#endif
