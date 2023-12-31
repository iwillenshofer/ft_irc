/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:22:55 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/17 16:07:55 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message(void) { }
Message::Message(std::string message): _message(message)
{
	_disassemble();
	_validate();
}
Message::Message(Message const &cp) { *this = cp; }
Message &Message::operator=(Message const &cp)
{
	_message = cp._message;
	_prefix = cp._prefix;
	_command = cp._command;
	_arguments = cp._arguments;
	return (*this);
}
Message::~Message() { }

/*
** getters
*/
std::string					&Message::message(void) { return (_message); }
std::string					&Message::prefix(void) { return (_prefix); }
std::string					&Message::command(void) { return (_command); }
std::vector<std::string>	&Message::arguments(void) { return (_arguments); }
std::string					&Message::arguments(size_t idx) { return (_arguments[idx]); }

/*
** disassembles _message into _prefix, _command and [_arguments]
*/
void Message::_disassemble(void)
{
	std::string user_message;
	std::string msg = _message;

	_message = ft::trim(_message);
	if (!msg.size())
		return;
	if (msg[0] == ':')
	{
		_prefix = msg.substr(0, msg.find(' '));
		msg.erase(0, _prefix.size());
		_prefix.erase(_prefix.begin());
		msg = ft::trim(msg);
	}
	if (msg.find(" :") != msg.npos)
	{
		user_message = ft::trim(msg.substr(msg.find(" :"), msg.size()));
		msg.erase(msg.size() - user_message.size());
		user_message.erase(0, 1);
	}
	msg = ft::trim(msg);
	_arguments = ft::split(msg, ' ');
	if (_arguments.size())
	{
		_command = _arguments[0];
		_arguments.erase(_arguments.begin());
	}
	if (user_message.size())
		_arguments.push_back(user_message);
	for (size_t i = 0; i < _arguments.size(); )
	{
		if (!(_arguments[i].size()))
			_arguments.erase(_arguments.begin() + i);
		else
		{
			i++;
		}
	}
	ft::uppercase(_command);
}

void Message::_validate(void)
{
	if (_message.size() > MSG_MAXMSGSIZE)
		throw InputLineTooLong();
	if (!(_message.size()) || !(_command.size()))
		throw EmptyMessage();
}

void Message::print(void)
{
	std::string args;
	
	for (std::vector<std::string>::iterator it = _arguments.begin(); it != _arguments.end(); it++)
		args = args + "'" + *it + "'" + (it != _arguments.end() - 1 ? "," : "");
	Debug("_message: " + _message);
	Debug("_prefix: " + _prefix);
	Debug("_command: " + _command);
	Debug("_arguments: [" + args + "]");
}

/*
** functions to validate strings/chars according to RFC2812 Section-2.3.1
** Message format in Augmented BNF
** https://datatracker.ietf.org/doc/html/rfc2812#section-2.3.1
*/

bool Message::is_bnf_target(std::string const &key)
{
	return (is_bnf_hostname(key) || is_bnf_hostaddr(key));
}

bool Message::is_bnf_msgtarget(std::string const &key)
{
	std::vector<std::string> v;

	if (!(key.size()))
		return (false);
	if (key[0] == ',' || key[key.size() - 1] == ',')
		return (false);
	v = ft::split(key, ',');
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
		if (!(is_bnf_msgto(*it)))
			return (false);
	return (true);			
}

bool Message::is_bnf_msgto(std::string const &key)
{
	std::vector<std::string> v;
	std::vector<std::string> v2;

	if (is_bnf_channel(key))
		return (true);
	v = ft::split(key, '@');
	if (v.size() == 2 || v.size() == 1)
	{
		v2 = ft::split(v[0], '%');
		if (v.size() == 2 && v2.size() == 2 && is_bnf_user(v2[0]) && is_bnf_host(v2[1]) && is_bnf_servername(v[1]))
			return (true);
		else if (v.size() == 2 && v2.size() == 1 && is_bnf_user(v[0]) && is_bnf_servername(v[1]))
			return (true);
		else if (v.size() == 1 && v2.size() == 2 && is_bnf_user(v[0]) && is_bnf_host(v[1]))
			return (true);
	}
	if (is_bnf_nickname(key))
		return (true);
	v = ft::split(key, '@');
	if (v.size() == 2)
	{
		v2 = ft::split(v[0], '!');
		if (v2.size() == 2 && is_bnf_nickname(v2[0]) && is_bnf_user(v2[1]) && is_bnf_host(v[1]))
			return (true);
	}
	return (false);
}

bool Message::is_bnf_channel(std::string const &key)
{
	std::string 			s(MSG_BNF_CHANNELTYPES);
	std::string 			substr;
	size_t					pos = 1;
	std::vector<std::string> v;

	if (!(key.size()))
		return (false);
	if (s.find(key[0]) == std::string::npos)
		return (false);
	if (key[0] == '!')
	{
		if (key.size() < 7)
			return (false);
		if (!(is_bnf_channelid(key.substr(1, 5))))
			return (false);
		pos = 6;
	}
	substr = key.substr(pos);
	if (!(substr.size()) || std::count(substr.begin(), substr.end(), ':') > 1 || substr[0] == ':' || substr[substr.size() - 1] == ':')
		return (0);
	v = ft::split(substr, ':');
	if (!(v.size()) || v.size() > 2)
		return (false);
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
		if (!(is_bnf_chanstring(*it)))
			return (false);
	return (true);
}

bool Message::is_bnf_servername(std::string const &key)
{
	return (is_bnf_host(key));
}

bool Message::is_bnf_host(std::string const &key)
{
	return (is_bnf_hostname(key) || is_bnf_hostaddr(key));
}

bool Message::is_bnf_hostname(std::string const &key)
{
	std::vector<std::string> v;
	if (!(key.size()))
		return (false);
	if (key.find("..") != std::string::npos || key[0] == '.' || key[key.size() - 1] == '.')
		return (false);
	v = ft::split(key, '.');
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
		if (!(is_bnf_shortname(*it)))
			return (false);
	return (true);
}

bool Message::is_bnf_shortname(std::string const &key)
{
	if (!(key.size()))
		return (false);
	if (!(is_bnf_letter(key[0])) && !(is_bnf_digit(key[0])))
		return (false);
	for (std::string::const_iterator it = key.begin(); it != key.end(); it++)
		if (!(is_bnf_letter(*it)) && !(is_bnf_digit(*it)) && *it != '-')
			return (false);
	if (key[key.size() - 1] == '-')
		return (false);
	return (true);
}

bool Message::is_bnf_hostaddr(std::string const &key)
{
	if (is_bnf_ipv4addr(key) || is_bnf_ipv6addr(key))
		return (true);
	return (false);
}

bool Message::is_bnf_ipv4addr_mask(std::string const &key)
{
	std::vector<std::string> v;

	if (!(key.size()))
		return (false);
	if (key[0] == '.' || key[key.size() - 1] == '.')
		return (false);
	v = ft::split(key, '.');
	if (v.size() < 2)
		return (false);
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
	{
		if (it->size() < 1 || it->size() > 3)
			return (false);
		for (std::string::iterator sit = it->begin(); sit != it->end(); sit++)
		{
			if (!(is_bnf_digit(*sit)) && !(*sit == '*') && !(*sit == '?'))
				return (false);
			if (*sit == '*' && it->size() != 1)
				return (false);
		}	
	}
	if (v[0].find('*') != std::string::npos || v[0].find('?') != std::string::npos || !(v.size()))
		return (false);
	return (true);
}

bool Message::is_bnf_ipv4addr(std::string const &key)
{
	std::vector<std::string> v;

	if (!(key.size()))
		return (false);
	if (key[0] == '.' || key[key.size() - 1] == '.')
		return (false);
	if (std::count(key.begin(), key.end(), '.') != 3)
		return (false);
	v = ft::split(key, '.');
	if (v.size() != 4)
		return (false);
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
	{
		if (it->size() < 1 || it->size() > 3)
			return (false);
		for (std::string::iterator sit = it->begin(); sit != it->end(); sit++)
			if (!(is_bnf_digit(*sit)))
				return (false);
	}
	return (true);
}

bool Message::is_bnf_ipv6addr(std::string const &key)
{
	std::vector<std::string> v;
	std::string substr;

	if (!(key.size()))
		return (false);
	if (key.find("0:0:0:0:0:") == 0)
	{
		substr = key.substr(10);
		v = ft::split(substr, ':');
		if (v.size() == 2 && (v[0] == "0" || v[0] == "FFFF") && is_bnf_ipv4addr(v[1]))
			return (true);
	}
	if (key[0] == ':' || key[key.size() - 1] == ':')
		return (false);
	if (std::count(key.begin(), key.end(), '.') != 7)
		return (false);
	v = ft::split(key, ':');
	if (v.size() != 8)
		return (false);
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
	{
		if (it->size() < 1)
			return (false);
		for (std::string::iterator sit = it->begin(); sit != it->end(); sit++)
			if (!(is_bnf_hexdigit(*sit)))
				return (false);
	}
	return (true);
}

bool Message::is_bnf_nickname(std::string const &nickname)
{
	if (!(nickname.size()) || nickname.size() > SRV_MAXNICKLEN)
		return (false);
	if (!(is_bnf_letter(nickname[0])) && !(is_bnf_special(nickname[0])))
		return (false);
	for (std::string::const_iterator it = nickname.begin(); it != nickname.end(); it++)
		if (!(is_bnf_letter(*it)) && !(is_bnf_special(*it)) && !(is_bnf_digit(*it)) && *it != '-')
			return (false);
	return (true);
}

/*
** Responses:
**  BNF_TARGETMSK_INVALID
**  BNF_TARGETMSK_VALID
**  BNF_TARGETMSK_NOTOPLEVEL
**  BNF_TARGETMSK_WILDTOPLEVEL
*/

int Message::is_bnf_targetmask(std::string const &_key)
{
	std::vector<std::string> v;
	std::string key = _key;

	if ((key.size()) < 2)
		return (BNF_TARGETMSK_INVALID);
	if (key[0] != '$' && key[0] != '#')
		return (BNF_TARGETMSK_INVALID);
	if (key.find('.') == std::string::npos || key[1] == '.' || key[key.size() - 1] == '.')
		return (BNF_TARGETMSK_INVALID);
	key.erase(key.begin());
	v = ft::split(key, '.');
	if (!(v.size()))
		return (BNF_TARGETMSK_NOTOPLEVEL);
	if (is_bnf_ipv4addr_mask(key) && (std::count(v.front().begin(), v.front().end(), '*') || std::count(v.front().begin(), v.front().end(), '?')))
		return (BNF_TARGETMSK_WILDTOPLEVEL);
	if (!(is_bnf_ipv4addr_mask(key)) && (std::count(v.back().begin(), v.back().end(), '*') || std::count(v.back().begin(), v.back().end(), '?')))
		return (BNF_TARGETMSK_WILDTOPLEVEL);
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
	{
		if (it->find("**") != std::string::npos)
			return (BNF_TARGETMSK_INVALID);
		for (std::string::iterator sit = it->begin(); sit != it->end(); sit++)
			if (*sit == '?' || *sit == '*')
				*sit = 'a';
		if (!(is_bnf_shortname(*it)))
			return (BNF_TARGETMSK_INVALID);
	}
	return (true);
}

bool Message::is_bnf_mask(std::string const &key)
{
	for (std::string::const_iterator it = key.begin(); it != key.end(); it++)
	{
		if (*it == 0)
			return (false);
		if ((*it == '*' || *it == '?') && (it != key.begin() && *(it - 1) == '\\'))
			return (false);
	}
	return (true);
}

bool Message::is_bnf_chanstring(std::string const &key)
{
	std::string s(MSG_BNF_CHANNELSTRFORBIDDEN);

	s.push_back('\0');
	for (std::string::const_iterator it = key.begin(); it != key.end(); it++)
	{
		if (*it < 0x01 || *it > 0x7f)
			return (false);
		for (std::string::const_iterator fbd = s.begin(); fbd != s.end(); fbd++)
		{
			if (*it == *fbd)
				return (false);
		}
	}
	return (true);
}

bool Message::is_bnf_channelid(std::string const &key)
{
	if (key.size() != MSG_BNF_CHANNELIDSIZE)
		return (false);
	for (std::string::const_iterator it = key.begin(); it != key.end(); it++)
	{
		if (!(is_bnf_digit(*it)) && (*it < 'A' || *it > 'Z'))
			return (false);
	}
	return (true);
}

bool Message::is_bnf_user(std::string const &key)
{
	std::string s(MSG_BNF_USERFORBIDDEN);

	s.push_back('\0');
	if (!(key.size()))
		return (false);
	for (std::string::const_iterator it = key.begin(); it != key.end(); it++)
	{
		if (*it < 0x01 || *it > 0x7f)
			return (false);
		for (std::string::const_iterator fbd = s.begin(); fbd != s.end(); fbd++)
			if (*it == *fbd)
				return (false);
	}
	return (true);
}

bool Message::is_bnf_key(std::string const &key)
{
	std::string s(MSG_BNF_KEYFORBIDDEN);

	s.push_back('\0');
	if (!(key.size()) || key.size() > 23)
		return (false);
	for (std::string::const_iterator it = key.begin(); it != key.end(); it++)
	{
		if (*it < 0x01 || *it > 0x7f)
			return (false);
		for (std::string::const_iterator fbd = s.begin(); fbd != s.end(); fbd++)
			if (*it == *fbd)
				return (false);
	}
	return (true);
}

bool Message::is_bnf_letter(const char c)
{
	std::string s(MSG_BNF_LETTER);

	for (std::string::iterator it = s.begin(); it != s.end(); it++)
		if (*it == c)
			return (true);
	return (false);
}

bool Message::is_bnf_numeric(std::string const &key)
{
	for (std::string::const_iterator it = key.begin(); it != key.end(); it++)
		if (!(is_bnf_digit(*it)))
			return (false);
	return (true);
}

bool Message::is_bnf_digit(const char c)
{
	std::string s(MSG_BNF_DIGIT);
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
		if (*it == c)
			return (true);
	return (false);
}

bool Message::is_bnf_hexdigit(const char c)
{
	std::string s(MSG_BNF_HEXDIGIT);

	if (is_bnf_digit(c))
		return (true);
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
		if (*it == c)
			return (true);
	return (false);
}

bool Message::is_bnf_special(const char c)
{
	std::string s(MSG_BNF_SPECIAL);

	for (std::string::iterator it = s.begin(); it != s.end(); it++)
		if (*it == c)
			return (true);
	return (false);
}

bool Message::has_bnf_wildcard(std::string s)
{
	ft::replace_string(s, "\\*", "x");
	ft::replace_string(s, "\\?", "x");
	if (s.find('?') != std::string::npos || s.find('*') != std::string::npos)
		return (true);
	return (false);
}

/*
** string functions
*/
void Message::clear_commas(std::string &s)
{
	remove_double_commas(s);
	if (s.size() && s[0] == ',')
		s.erase(s.begin());
	if (s.size() && s[s.size() - 1] == ',')
		s.erase(s.size() - 1);
}

void Message::remove_double_commas(std::string &s)
{
	while (s.find(",,") != std::string::npos)
		s.replace(s.find(",,"), 2, ",");
}

std::vector<std::string> Message::split_commas(std::string s, bool trim_commas)
{
	if (trim_commas)
		clear_commas(s);
	else
		remove_double_commas(s);
	return (ft::split(s, ','));
}

const char*	Message::InputLineTooLong::what() const throw() { return ("417: Input line was too long."); }

const char*	Message::EmptyMessage::what() const throw() { return ("Empty Message."); }
