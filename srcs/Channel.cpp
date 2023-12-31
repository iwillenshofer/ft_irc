/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:41:52 by roman             #+#    #+#             */
/*   Updated: 2022/02/21 20:50:11 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(void) { }

Channel::Channel(std::string name, Client &creator): _user_limit(0)
{
	_creator = &creator;
	set_name(name);
	users.push_back(_creator);
	_operators.push_back(_creator);
}

Channel::Channel(Channel const &cp)
{
	*this = cp;
}

Channel & Channel::operator=(Channel const &cp)
{
	_name = cp._name;
	_creator = cp._creator;
	_topic = cp._topic;
	_password = cp._password;
	_mode = cp._mode;
	_user_limit = cp._user_limit;
	users = cp.users;
	_operators = cp._operators;
	_voices = cp._voices;
	_bans = cp._bans;
	_invitations = cp._invitations;
	
	return (*this);
}

Channel::~Channel(void)
{
	return ;
}

void	Channel::set_name(std::string name)
{
	if (Message::is_bnf_channel(name) == false)
		throw (ERR_BADCHANMASK);
	_name = name;
}

std::string	Channel::get_name(void) const
{
	return _name;
}

Client *Channel::get_creator(void) const
{
	return _creator;
}

void	Channel::set_topic(Client &nick, std::string topic)
{
	if (_mode.t == true)
	{
		if (is_operator(nick) == false)
			throw (ERR_CHANOPRIVSNEEDED);		
	}
	_topic = topic;
}

std::string	Channel::get_topic(void) const
{
	return _topic;
}

bool		Channel::match_password(std::string password) const
{
	if (_mode.k && password != _password)
		return (false);
	return (true);
}

void	Channel::set_password(Client &chanop, std::string key)
{
	if (key.empty() == true)
		throw (ERR_NEEDMOREPARAMS);
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	if (_mode.k == true)
		throw (ERR_KEYSET);
	_password = key;
	_mode.k = true;
}

void	Channel::unset_password(Client &chanop, std::string key)
{
	if (key.empty() == true)
		throw (ERR_NEEDMOREPARAMS);
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	if (key != _password)
		throw (ERR_KEYSET);
	_password = "";
	_mode.k = false;
}

bool	Channel::get_mode(char mode) const
{
	switch (mode)
	{
		case 'a':
			return _mode.a;
			break;
		case 'i':
			return _mode.i;
			break;
		case 'm':
			return _mode.m;
			break;
		case 'n':
			return _mode.n;
			break;
		case 'q':
			return _mode.q;
			break;
		case 'p':
			return _mode.p;
			break;
		case 's':
			return _mode.s;
			break;
		case 'r':
			return _mode.r;
			break;
		case 't':
			return _mode.t;
			break;
		case 'k':
			return _mode.k;
			break;
		case 'l':
			return _mode.l;
			break;
		default:
			return false;
			break;
	}
}

std::string	Channel::get_modes(void) const
{
	std::string m = "+";

	if (_mode.a) m += 'a';
	if (_mode.i) m += 'i';
	if (_mode.m) m += 'm';
	if (_mode.n) m += 'n';
	if (_mode.q) m += 'q';
	if (_mode.p) m += 'p';
	if (_mode.s) m += 's';
	if (_mode.r) m += 'r';
	if (_mode.t) m += 't';
	if (_mode.k) m += 'k';
	if (_mode.l) m += 'l';
	return (m);
}

std::string	Channel::get_mode_params(void) const
{
	std::string m;

	if (_mode.k) m += ft::to_string(_password) + " ";
	if (_mode.l) m += ft::to_string(_user_limit);
	if (m.size() && m[m.size() - 1] == ' ')
		m.erase(m.size() - 1, 1);
	return (m);
}

void	Channel::activate_mode(Client &nick, char flag, std::string arg, Client *target)
{
	if (flag == 'b')
		add_ban(nick, arg);
	else if (flag == 'i')
		set_invitation(nick);
	else if (flag == 'l')
		set_user_limit(nick, arg);
	else if (flag == 'm')
		set_moderated(nick);
	else if (flag == 'n')
		set_no_outside(nick);
	else if (flag == 'o')
		add_operator(nick, target);
	else if (flag == 'p')
		set_private(nick);
	else if (flag == 's')
		set_secret(nick);
	else if (flag == 't')
		set_change_topic(nick);
	else if (flag == 'k')
		set_password(nick, arg);
	else if (flag == 'v')
		add_voice(nick, target);
}

void	Channel::deactivate_mode(Client &nick, char flag, std::string arg, Client *target)
{
	if (flag == 'b')
		remove_ban(nick, arg);
	else if (flag == 'i')
		unset_invitation(nick);
	else if (flag == 'l')
		unset_user_limit(nick);
	else if (flag == 'm')
		unset_moderated(nick);
	else if (flag == 'n')
		unset_no_outside(nick);
	else if (flag == 'o')
		remove_operator(nick, target);
	else if (flag == 'p')
		unset_private(nick);
	else if (flag == 's')
		unset_secret(nick);
	else if (flag == 't')
		unset_change_topic(nick);
	else if (flag == 'k')
		unset_password(nick, arg);
	else if (flag == 'v')
		remove_voice(nick, target);
}

void	Channel::set_user_limit(Client &chanop, std::string limit)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	else if (!(Message::is_bnf_numeric(limit)))
		throw (ERR_SILENT);
	_user_limit = atoi(limit.c_str());
	if (_user_limit < 1)
	{
		_user_limit = 0;
		return ;
	}
	_mode.l = true;
}

void	Channel::unset_user_limit(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_user_limit = 0;
	_mode.l = false;
}

bool Channel::is_user(Client &nick)
{
	for (std::vector<Client *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if (*it == &nick)
			return true;
	}
	return false;
}

void Channel::add_user(Client &nick, std::string password)
{
	if (is_invitation(nick) == true)
		users.push_back(&nick);
	else if(_mode.i == true)
		throw (ERR_INVITEONLYCHAN);
	else if (_mode.l == true && users.size() >= _user_limit)
		throw (ERR_CHANNELISFULL);
	else if (is_banned(nick) == true)
		throw (ERR_BANNEDFROMCHAN);	
	else if (!(match_password(password)))
		throw (ERR_BADCHANNELKEY);
	else
		users.push_back(&nick);	
	remove_invitation(nick);
}

void Channel::remove_user(Client &nick)
{
	for (std::vector<Client *>::iterator it = users.begin(); it != users.end(); it++)
	{
		if (*it == &nick)
		{
			users.erase(it);
			break ;
		}
	}
	for (std::vector<Client *>::iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if (*it == &nick)
		{
			_operators.erase(it);
			return;
		}
	}
	for (std::vector<Client *>::iterator it = _voices.begin(); it != _voices.end(); it++)
	{
		if (*it == &nick)
		{
			_voices.erase(it);
			return;
		}
	}
}

bool	Channel::is_operator(Client &nick)
{
	for (std::vector<Client *>::iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if (*it == &nick)
			return true;
	}
	return false;
}

void	Channel::add_operator(Client &chanop, Client *nick)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);	
	if (!(nick) ||is_user(*nick) == false)
		throw (ERR_NOSUCHNICK);
	_operators.push_back(nick);
}

void	Channel::remove_operator(Client &chanop, Client *nick)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	if (!(nick))
		throw (ERR_NOSUCHNICK);
	for (std::vector<Client *>::iterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if (*it == nick)
		{
			_operators.erase(it);
			return;
		}
	}
	throw (ERR_NOSUCHNICK);
}

bool	Channel::is_voice(Client &nick)
{
	for (std::vector<Client *>::iterator it = _voices.begin(); it != _voices.end(); it++)
	{
		if (*it == &nick)
			return true;
	}
	return false;
}

void	Channel::add_voice(Client &chanop, Client *nick)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);	
	if (!(nick) || is_user(*nick) == false)
		throw (ERR_NOSUCHNICK);
	_voices.push_back(nick);
}

void	Channel::remove_voice(Client &chanop, Client *nick)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);	
	if (!(nick))
		throw (ERR_NOSUCHNICK);
	for (std::vector<Client *>::iterator it = _voices.begin(); it != _voices.end(); it++)
	{
		if (*it == nick)
		{
			_voices.erase(it);
			return;
		}
	}
	throw (ERR_NOSUCHNICK);
}

std::vector<std::string>	&Channel::get_ban_list(void)
{
	return (_bans);
}


bool	Channel::is_banned(Client &client)
{
	for (std::vector<std::string>::iterator it = _bans.begin(); it != _bans.end(); it++)
	{
		if (Mask::match(client, *it))
			return true;
	}
	return false;
}

bool	Channel::is_banned(std::string mask)
{
	for (std::vector<std::string>::iterator it = _bans.begin(); it != _bans.end(); it++)
	{
		if (Mask::match(mask, *it))
			return true;
	}
	return false;
}

void	Channel::add_ban(Client &chanop,  std::string mask)
{
	std::string _mask = Mask::create(mask);

	if (is_operator(chanop) == false) throw (ERR_CHANOPRIVSNEEDED);	
	for (std::vector<std::string>::iterator it = _bans.begin(); it != _bans.end(); it++)
	{
		if (*it == _mask)
			return ;
	}
	_bans.push_back(_mask);
}

void	Channel::remove_ban(Client &chanop, std::string mask)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);	
	for (std::vector<std::string>::iterator it = _bans.begin(); it != _bans.end(); it++)
	{
		if (*it == mask)
		{
			_bans.erase(it);
			return;
		}
	}
}

bool    Channel::is_invitation_only(void) const
{
	return (_mode.i);
}

void	Channel::set_invitation(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_mode.i = true;
}

void	Channel::unset_invitation(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_invitations.clear();
	_mode.i = false;
}

bool	Channel::is_invitation(Client &nick)
{
	for (std::vector<Client *>::iterator it = _invitations.begin(); it != _invitations.end(); it++)
	{
		if (*it == &nick)
			return true;
	}
	return false;
}

void	Channel::add_invitation(Client &chanop, Client &nick)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	if (is_user(nick) == true)
		throw (ERR_USERONCHANNEL);
	_invitations.push_back(&nick);
}

void	Channel::add_invitation(Client &nick)
{
	if (!(is_invitation(nick)))
		_invitations.push_back(&nick);
}

void	Channel::remove_invitation(Client &nick)
{
	for (std::vector<Client *>::iterator it = _invitations.begin(); it != _invitations.end(); it++)
	{
		if (*it == &nick)
		{
			std::cout << "addr1: "  << *it << " addr2:" << &nick << std::endl;
			_invitations.erase(it);
			return;
		}
	}
}

bool	Channel::is_moderated(void) { return (_mode.m); }

void	Channel::set_moderated(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_mode.m = true;
}

void	Channel::unset_moderated(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_mode.m = false;
}

bool	Channel::is_no_outside(void) { return (_mode.n); }

void	Channel::set_no_outside(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_mode.n = true;
}

void	Channel::unset_no_outside(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_mode.n = false;
}

bool	Channel::is_private(void) { return (_mode.p); }

void	Channel::set_private(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_mode.p = true;
}

void	Channel::unset_private(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_mode.p = false;
}

bool	Channel::is_secret(void) { return (_mode.s); }

void	Channel::set_secret(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_mode.s = true;
}

void	Channel::unset_secret(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_mode.s = false;
}

void	Channel::set_change_topic(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_mode.t = true;
}

void	Channel::unset_change_topic(Client &chanop)
{
	if (is_operator(chanop) == false)
		throw (ERR_CHANOPRIVSNEEDED);
	_mode.t = false;
}

bool	Channel::can_speak(Client &nick)
{
	if (is_banned(nick) || _mode.m == true)
	{
		if (!is_operator(nick) && !is_voice(nick))
			return false;
	}
	else if (is_no_outside() && !(is_user(nick)))
		return false;
	return true;
}

/*
void		Channel::change_nick(std::string oldnick, std::string newnick)
{
	for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); it++)
		if (*it == oldnick)
			*it = newnick;
	for (std::vector<std::string>::iterator it = _operators.begin(); it != _operators.end(); it++)
		if (*it == oldnick)
			*it = newnick;
	for (std::vector<std::string>::iterator it = _voices.begin(); it != _voices.end(); it++)
		if (*it == oldnick)
			*it = newnick;
	for (std::vector<std::string>::iterator it = _invitations.begin(); it != _invitations.end(); it++)
		if (*it == oldnick)
			*it = newnick;
}
*/
bool		Channel::is_empty(void) { return (users.size() == 0); }
