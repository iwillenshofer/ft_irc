/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:41:52 by roman             #+#    #+#             */
/*   Updated: 2022/01/30 20:50:06 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(void)
{
    //here
}

Channel::Channel(std::string name, std::string creator): _user_limit(0)
{
	set_name(name);
	users.push_back(creator);
	_operators.push_back(creator);
	bzero(&_mode, sizeof(t_channelmode));
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

std::string	Channel::get_creator(void) const
{
	return _creator;
}

void	Channel::set_topic(std::string nick, std::string topic)
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

void	Channel::set_password(std::string chanop, std::string key)
{
    if (key.empty() == true)
        throw (ERR_NEEDMOREPARAMS);
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    if (_password.empty() == false)
        throw (ERR_KEYSET);
    _password = key;
    _mode.k = true;
}

void	Channel::unset_password(std::string chanop, std::string key)
{
    if (key.empty() == true)
        throw (ERR_NEEDMOREPARAMS);
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    if (key != _password)
        throw (ERR_KEYSET);
    _password.erase();
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

	if (_mode.k) m += " " + ft::to_string(_password);
	if (_mode.l) m += " " + ft::to_string(_user_limit);
	return (m);
}

void	Channel::activate_mode(std::string nick, char flag, std::string arg)
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
        add_operator(nick, arg);
    else if (flag == 'p')
        set_private(nick);
    else if (flag == 's')
        set_secret(nick);
    else if (flag == 't')
        set_change_topic(nick);
    else if (flag == 'k')
        set_password(nick, arg);
    else if (flag == 'v')
        add_voice(nick, arg);
}

void	Channel::deactivate_mode(std::string nick, char flag, std::string arg)
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
        remove_operator(nick, arg);
    else if (flag == 'p')
        unset_private(nick);
    else if (flag == 's')
        unset_secret(nick);
    else if (flag == 't')
        unset_change_topic(nick);
    else if (flag == 'k')
        unset_password(nick, arg);
    else if (flag == 'v')
        remove_voice(nick, arg);
}

void	Channel::set_user_limit(std::string chanop, std::string limit)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _user_limit = atoi(limit.c_str());
    if (_user_limit < 1)
    {
        _user_limit = 0;
        return ;
    }
    _mode.l = true;
}

void	Channel::unset_user_limit(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _user_limit = 0;
    _mode.l = false;
}

bool Channel::is_user(std::string nick)
{
    for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); it++)
    {
        if (*it == nick)
            return true;
    }
    return false;
}


void Channel::add_user(std::string nick, std::string password)
{
    if (is_invitation(nick) == true)
        users.push_back(nick);
    else if(_mode.i == true)
        throw (ERR_INVITEONLYCHAN);
    else if (_mode.l == true && users.size() >= _user_limit)
        throw (ERR_CHANNELISFULL);
    else if (is_banned(nick) == true)
        throw (ERR_BANNEDFROMCHAN);	
    else if (!(match_password(password)))
	    throw (ERR_BADCHANNELKEY);
    else
        users.push_back(nick);	
    remove_invitation(nick);
}

void Channel::remove_user(std::string nick)
{
    for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); it++)
    {
        if (*it == nick)
        {
            users.erase(it);
            break ;
        }
    }
    for (std::vector<std::string>::iterator it = _operators.begin(); it != _operators.end(); it++)
    {
        if (*it == nick)
        {
            _operators.erase(it);
            return;
        }
    }
    for (std::vector<std::string>::iterator it = _voices.begin(); it != _voices.end(); it++)
    {
        if (*it == nick)
        {
            _voices.erase(it);
            return;
        }
    }
}

bool	Channel::is_operator(std::string nick)
{
    for (std::vector<std::string>::iterator it = _operators.begin(); it != _operators.end(); it++)
    {
        if (*it == nick)
            return true;
    }
    return false;
}

void	Channel::add_operator(std::string chanop, std::string nick)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);	
    if (is_user(nick) == false)
        throw (ERR_NOSUCHNICK);
    _operators.push_back(nick);
}

void	Channel::remove_operator(std::string chanop, std::string nick)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);	
    for (std::vector<std::string>::iterator it = _operators.begin(); it != _operators.end(); it++)
    {
        if (*it == nick)
        {
            it->erase();
            return;
        }
    }
    throw (ERR_NOSUCHNICK);
}

bool	Channel::is_voice(std::string nick)
{
    for (std::vector<std::string>::iterator it = _voices.begin(); it != _voices.end(); it++)
    {
        if (*it == nick)
            return true;
    }
    return false;
}

void	Channel::add_voice(std::string chanop, std::string nick)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);	
    if (is_user(nick) == false)
        throw (ERR_NOSUCHNICK);
    _voices.push_back(nick);
}

void	Channel::remove_voice(std::string chanop, std::string nick)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);	
    for (std::vector<std::string>::iterator it = _voices.begin(); it != _voices.end(); it++)
    {
        if (*it == nick)
        {
            it->erase();
            return;
        }
    }
    throw (ERR_NOSUCHNICK);
}

bool	Channel::is_banned(Client &client)
{
    // TO do : Add mask : *
    for (std::vector<std::string>::iterator it = _bans.begin(); it != _bans.end(); it++)
    {
        if (Mask::match(client, *it))
            return true;
    }
    return false;
}

bool	Channel::is_banned(std::string nick)
{
    // TO do : Add mask : *
    for (std::vector<std::string>::iterator it = _bans.begin(); it != _bans.end(); it++)
    {
        if (*it == nick)
            return true;
    }
    return false;
}

void	Channel::add_ban(std::string chanop, std::string nick)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);	
    if (is_banned(nick)) // If user is already ban, we can return
        return ;
    _bans.push_back(nick);
}

void	Channel::remove_ban(std::string chanop, std::string nick)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);	
    for (std::vector<std::string>::iterator it = _bans.begin(); it != _bans.end(); it++)
    {
        if (*it == nick)
        {
            it->erase();
            return;
        }
    }
}

bool    Channel::is_invitation_only(void) const
{
    return (_mode.i);
}

void	Channel::set_invitation(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _mode.i = true;
}

void	Channel::unset_invitation(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _invitations.clear();
    _mode.i = false;
}

bool	Channel::is_invitation(std::string nick)
{
    for (std::vector<std::string>::iterator it = _invitations.begin(); it != _invitations.end(); it++)
    {
        if (*it == nick)
            return true;
    }
    return false;
}

void	Channel::add_invitation(std::string chanop, std::string nick)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    if (is_user(nick) == true)
        throw (ERR_USERONCHANNEL);
    _invitations.push_back(nick);
}

void	Channel::add_invitation(std::string nick)
{
    _invitations.push_back(nick);
}

void	Channel::remove_invitation(std::string nick)
{
    for (std::vector<std::string>::iterator it = _invitations.begin(); it != _invitations.end(); it++)
    {
        if (*it == nick)
        {
            it->erase();
            return;
        }
    }
}

bool	Channel::is_moderated(void) { return (_mode.m); }

void	Channel::set_moderated(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _mode.m = true;
}

void	Channel::unset_moderated(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _mode.m = false;
}

bool	Channel::is_no_outside(void) { return (_mode.n); }

void	Channel::set_no_outside(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _mode.n = true;
}

void	Channel::unset_no_outside(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _mode.n = false;
}

bool	Channel::is_private(void) { return (_mode.p); }

void	Channel::set_private(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _mode.p = true;
}

void	Channel::unset_private(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _mode.p = false;
}

bool	Channel::is_secret(void) { return (_mode.s); }

void	Channel::set_secret(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _mode.s = true;
}

void	Channel::unset_secret(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _mode.s = false;
}

void	Channel::set_change_topic(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _mode.t = true;
}

void	Channel::unset_change_topic(std::string chanop)
{
    if (is_operator(chanop) == false)
        throw (ERR_CHANOPRIVSNEEDED);
    _mode.t = false;
}

bool	Channel::can_speak(std::string nick)
{
    if (is_user(nick) == true)
    {
        if (is_banned(nick) == true || _mode.m == true)
        {
            if (is_operator(nick) == true || is_voice(nick) == true)
                return true;
            return false;
        }
    }
    return true;
}

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

bool		Channel::is_empty(void) { return (users.size() == 0); }
