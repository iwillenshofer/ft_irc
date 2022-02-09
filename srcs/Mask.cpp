/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mask.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:05:41 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/09 19:29:33 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mask.hpp"

Mask::Mask(void) { }
Mask::Mask(Mask const &cp) { *this = cp; }
Mask &Mask::operator=(Mask const &cp)	{ (void)cp; return (*this); }
Mask::~Mask() { }

Mask::Maskparts::Maskparts(void) { }
Mask::Maskparts::Maskparts(std::string s) { _strip(s); }
Mask::Maskparts::Maskparts(Maskparts const &cp) { *this = cp; }
Mask::Maskparts &Mask::Maskparts::operator=(Maskparts const &cp)
{
	nickname = cp.nickname;
	username = cp.username;
	hostname = cp.hostname;
	return (*this);
}
Mask::Maskparts::~Maskparts() { }
std::string Mask::Maskparts::fullmask( void ) { return (nickname + "!" + username + "@" + hostname); }
std::string Mask::Maskparts::_striphost(std::string &string)
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

std::string Mask::Maskparts::_stripuser(std::string &string)
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

void Mask::Maskparts::_strip(std::string string)
{
	hostname = _striphost(string);
	username = _stripuser(string);
	nickname = string;
	ft::replace_string(hostname, "**", "*");
	ft::replace_string(username, "**", "*");
	ft::replace_string(nickname, "**", "*");
	if (!(hostname.size()))
		hostname = "*";
	if (!(username.size()))
		username = "*";
	if (!(nickname.size()))
		nickname = "*";
}

bool	Mask::_match(std::string::iterator target, std::string::iterator mask, std::string::iterator t_end, std::string::iterator m_end)
{
    if (mask == m_end && target == t_end)
        return true;
    if (mask != m_end && (mask + 1) != m_end && target == t_end && *mask == '*')
        return false;
    if (mask != m_end && target != t_end && (*mask == '?' || *mask == *target))
        return (_match(target + 1, mask + 1, t_end, m_end));
    if (mask != m_end && *mask == '*')
        return (_match(target, mask + 1, t_end, m_end) || _match(target + 1, mask, t_end, m_end));
    return false;
}

bool	Mask::match(Client &client, std::string mask)
{
	Maskparts mp_target;
	Maskparts mp_mask(mask);

	mp_target.hostname = client.hostname;
	mp_target.nickname = client.nickname;
	mp_target.username = client.username;
	return (match(mp_target, mp_mask));
}

bool	Mask::match(std::string target, std::string mask)
{
	Maskparts mp_target(target);
	Maskparts mp_mask(mask);

	return (match(mp_target, mp_mask));
}

bool	Mask::match(Maskparts &target, Maskparts &mask)
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

/*
** match raw:
** matches a string against a mask without parsing it into username, nickname
** and hostname 
*/
bool	Mask::match_raw(std::string target, std::string mask)
{
	Debug("Match: " + target + " to " + mask, DBG_ERROR);
	return (_match(target.begin(), mask.begin(), target.end(), mask.end()));
}

std::string Mask::create(std::string target)
{
	ft::replace_string(target, "**", "*");
	return (Maskparts(target).fullmask());
}
