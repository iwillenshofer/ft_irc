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

class Mask
{
	public:
		Mask(void) { };
		Mask(Mask const &cp) { *this = cp; }
		Mask &operator=(Mask const &cp)	{ return (*this); }
		virtual ~Mask() { };
	
		class Maskparts
		{
			public:
				Maskparts(void) { };
				Maskparts(std::string s) { _strip(s); };
				Maskparts(Mask const &cp) { *this = cp; }
				Maskparts &operator=(Maskparts const &cp)
				{
					nickname = cp.nickname;
					username = cp.username;
					hostname = cp.hostname;
					return (*this);
				}
				virtual ~Maskparts() { };
				std::string nickname;
				std::string username;
				std::string hostname;
				std::string fullmask( void ) { return (nickname + "!" + username + "@" + hostname); }

			private:
				static std::string _striphost(std::string &string)
				{
					size_t pos;
					std::string ret;

					pos =  string.find('@');
					if (pos != std::string::npos)
					{
						ret = string.substr(pos + 1);
						string = string.substr(0, pos);
						return (ret);
					}
					return ("");
				}
				
				static std::string _stripuser(std::string &string)
				{
					size_t pos;
					std::string ret;

					pos =  string.find('!');
					if (pos != std::string::npos)
					{
						ret = string.substr(pos + 1);
						string = string.substr(0, pos);
						return (ret);
					}
					return ("");
				}

				void _strip(std::string string)
				{
					hostname = _striphost(string);
					username = _stripuser(string);
					nickname = string;
					if (!(hostname.size()))
						hostname = "*";
					if (!(username.size()))
						username = "*";
					if (!(nickname.size()))
						nickname = "*";
				}
		};

	private:

		static bool	_match(std::string::iterator target, std::string::iterator mask, std::string::iterator t_end, std::string::iterator m_end)
		{
			if (target == t_end && mask == m_end)
				return (true);
			if (mask != m_end && *mask == '*' && (mask + 1 != m_end) && target == t_end)
				return (false);
			if (mask != m_end && target != t_end && ( *mask == '?' || *mask == *target))
				return (_match(++target, ++mask, t_end, m_end));
			if (mask != m_end && *mask == '*')
				return (_match(target + 1, mask, t_end, m_end) || _match(target, ++mask, t_end, m_end));
			return (false);
		}

	public:
		/*
		** getters
		*/
		static bool	match(Client &client, std::string mask)
		{
			Maskparts mp_target;
			Maskparts mp_mask(mask);

			mp_target.hostname = client.hostname;
			mp_target.nickname = client.nickname;
			mp_target.username = client.username;
			return (match(mp_target, mp_mask));
		}

		static bool	match(std::string target, std::string mask)
		{
			Maskparts mp_target(target);
			Maskparts mp_mask(mask);

			return (match(mp_target, mp_mask));
		}

		static bool	match(Maskparts &target, Maskparts &mask)
		{
			Debug("Matching username: " + target.username + "  -  " + mask.username + " : " + (_match(target.username.begin(),mask.username.begin(), target.username.end(),mask.username.end()) ? "TRUE" : "FALSE"), DBG_DEV);
			Debug("Matching nickname: " + target.nickname + "  -  " + mask.nickname + " : " + (_match(target.nickname.begin(),mask.nickname.begin(), target.nickname.end(),mask.nickname.end()) ? "TRUE" : "FALSE"), DBG_DEV);
			Debug("Matching hostname: " + target.hostname + "  -  " + mask.hostname + " : " + (_match(target.hostname.begin(),mask.hostname.begin(), target.hostname.end(),mask.hostname.end()) ? "TRUE" : "FALSE"), DBG_DEV);
			if (!(_match(target.hostname.begin(),mask.hostname.begin(), target.hostname.end(),mask.hostname.end())))
				return (false);
			if (!(_match(target.nickname.begin(),mask.nickname.begin(), target.nickname.end(),mask.nickname.end())))
				return (false);
			if (!(_match(target.username.begin(),mask.username.begin(), target.username.end(),mask.username.end())))
				return (false);
			return (true);
		}

		static std::string create(std::string target) { return (Maskparts(target).fullmask()); }
};

#endif
