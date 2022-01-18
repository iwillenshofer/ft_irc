/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 22:50:49 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/16 11:27:02 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <string>
# include <algorithm>
/*
** channel modes. currently a struct, but will be converted into a class so it can initialize itself.
*/
typedef struct s_channelmode
{
	bool O; // give "channel creator" status;
	bool o; // give/take channel operator privilege;
	bool v; // give/take the voice privilege;
	bool a; // toggle the anonymous channel flag;
	bool i; // toggle the invite-only channel flag;
	bool m; // toggle the moderated channel;
	bool n; // toggle the no messages to channel from clients on the outside;
	bool q; // toggle the quiet channel flag;
	bool p; // toggle the private channel flag;
	bool s; // toggle the secret channel flag;
	bool r; // toggle the server reop channel flag;
	bool t; // toggle the topic settable by channel operator only flag;
	bool k; // set/remove the channel key (password);
	bool l; // set/remove the user limit to channel;
	bool b; // set/remove ban mask to keep users out;
	bool e; // set/remove an exception mask to override a ban mask;
	bool I; // set/remove an invitation mask to automatically overridethe invite-only flag;
} t_channelmode;
class Channel
{
	public:

		Channel(std::string name, std::string creator): user_limit(0)
		{
			set_name(name);
			users.push_back(creator);
			operators.push_back(creator);
			bzero(&mode, sizeof(t_channelmode));
		} 

		Channel(Channel const &cp) { *this = cp; }

		Channel &operator=(Channel const &cp)
		{
			name = cp.name;
			mode = cp.mode;
			creator = cp.creator;
			users = cp.users;
			operators = cp.operators;
			voices = cp.voices;
			user_limit = cp.user_limit;
			channel_key = cp.channel_key;
			bans = cp.bans;
			invitations = cp.invitations;
			return (*this);
		}
		virtual ~Channel() { };
	
	public:
		std::string					name;
		t_channelmode 				mode;
		std::string 				creator;
		std::vector<std::string> 	users;
		std::vector<std::string> 	operators;
		std::vector<std::string> 	voices;
		int							user_limit;
		std::string					channel_key;
		std::vector<std::string>	bans;
		std::vector<std::string>	invitations;
		std::string					password;
		std::string					_topic;

	public:
		bool is_user(std::string nick)
		{
			for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); it++)
			{
				if (*it == nick)
					return true;
			}
			return false;
		}
		
		void add_user(std::string nick)
		{
			if (user_limit != 0 && users.size() >= user_limit)
				throw std::runtime_error("Cannot join channel (+l): Code 471");
			if (is_banned(nick) == true)
				throw std::runtime_error("Cannot join channel (+b): Code 471");
			for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); it++)
			{
				if (*it == nick)
				break ;
			}		
			users.push_back(nick);
		}

		void remove_user(std::string nick)
		{
			for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); it++)
			{
				if (*it == nick)
				{
					users.erase(it);
					return ;
				}
			}
		}

		void	set_name(std::string name)
		{
			if (name.at(0) != '&' || name.at(0) != '#' || name.at(0) != '+' || name.at(0) != '!')
				throw std::runtime_error("Invalid channel name : Code 476");
			if (name.size() > 50)
				throw std::runtime_error("Invalid channel name: Code 476");
			for (std::string::iterator it = name.begin(); it != name.end(); it++)
			{
				if (*it == ' ' || *it == 7 || *it == ',' || *it == ':')
					throw std::runtime_error("Invalid channel name: Code 476");
			}
		}

		void	activate_mode(std::string nick, char flag, std::string arg)
		{
			if (flag == 'b')
				add_ban(nick, arg);
			else if (flag == 'i')
				set_invitation(nick);
			else if (flag == 'l')
				set_limit(nick, arg);
			else if (flag == 'm')
				set_moderated(nick);
			else if (flag == 'n')
				mode.n = true;
			else if (flag == 'o')
				add_operator(nick, arg);
			else if (flag == 'p')
				mode.p = true;
			else if (flag == 's')
				mode.s = true;
			else if (flag == 't')
				mode.t = true;
			else if (flag == 'k')
				set_password(nick, arg);
			else if (flag == 'v')
				add_voice(nick, arg);
			
		}

		void	desactivate_mode(std::string nick, char flag, std::string arg)
		{
			if (flag == 'b')
				remove_ban(nick, arg);
			else if (flag == 'i')
				unset_invitation(nick);
			else if (flag == 'l')
				unset_limit(nick);
			else if (flag == 'm')
				mode.m = true;
			else if (flag == 'n')
				mode.n = true;
			else if (flag == 'o')
				remove_operator(nick, arg);
			else if (flag == 'p')
				mode.p = true;
			else if (flag == 's')
				mode.s = true;
			else if (flag == 't')
				mode.t = true;
			else if (flag == 'k')
				unset_password(nick, arg);
			else if (flag == 'v')
				remove_voice(nick, arg);
		}

		// operators

		bool	is_operator(std::string nick)
		{
			for (std::vector<std::string>::iterator it = operators.begin(); it != operators.end(); it++)
			{
				if (*it == nick)
					return true;
			}
			return false;
		}

		void	add_operator(std::string chanop, std::string nick)
		{
			if (is_operator(chanop) == false)
				throw std::runtime_error("You're not channel operator: Code 482");	
			if (is_user(nick) == false)
				throw std::runtime_error("No such nick: Code 401");
			operators.push_back(nick);
		}

		void	remove_operator(std::string chanop, std::string nick)
		{
			if (is_operator(chanop) == false)
				throw std::runtime_error("You're not channel operator: Code 482");	
			for (std::vector<std::string>::iterator it = operators.begin(); it != operators.end(); it++)
			{
				if (*it == nick)
				{
					it->erase();
					return;
				}
			}
			throw std::runtime_error("No such nick: Code 401");
		}

		// ban

		bool	is_banned(std::string nick)
		{
			for (std::vector<std::string>::iterator it = bans.begin(); it != bans.end(); it++)
			{
				if (*it == nick)
					return true;
			}
			return false;
		}

		void	add_ban(std::string chanop, std::string nick)
		{
			if (is_operator(chanop) == false)
				throw std::runtime_error(":You're not channel operator: Code 482");	
			if (is_banned(nick)) // If user is already ban, we can return
				return ;
			bans.push_back(nick);
		}

		void	remove_ban(std::string chanop, std::string nick)
		{
			if (is_operator(chanop) == false)
				throw std::runtime_error(":You're not channel operator: Code 482");	
			for (std::vector<std::string>::iterator it = bans.begin(); it != bans.end(); it++)
			{
				if (*it == nick)
				{
					it->erase();
					return;
				}
			}
		}

		// voice

		bool	is_voice(std::string nick)
		{
			for (std::vector<std::string>::iterator it = voices.begin(); it != voices.end(); it++)
			{
				if (*it == nick)
					return true;
			}
			return false;
		}

		void	add_voice(std::string chanop, std::string nick)
		{
			if (is_operator(chanop) == false)
				throw std::runtime_error("You're not channel operator: Code 482");	
			if (is_user(nick) == false)
				throw std::runtime_error("No such nick: Code 401");
			voices.push_back(nick);
		}

		void	remove_voice(std::string chanop, std::string nick)
		{
			if (is_operator(chanop) == false)
				throw std::runtime_error("You're not channel operator: Code 482");	
			for (std::vector<std::string>::iterator it = voices.begin(); it != voices.end(); it++)
			{
				if (*it == nick)
				{
					it->erase();
					return;
				}
			}
			throw std::runtime_error("No such nick: Code 401");
		}

		// limit user

		void	set_limit(std::string chanop, std::string limit)
		{
			if (is_operator(chanop) == false)
				throw std::runtime_error("You're not channel operator: Code 482");
			user_limit = atoi(limit.c_str());
			if (user_limit < 1)
			{
				user_limit = 0;
				return ;
			}
			mode.l = true;
		}

		void	unset_limit(std::string chanop)
		{
			if (is_operator(chanop) == false)
				throw std::runtime_error("You're not channel operator: Code 482");
			user_limit = 0;
			mode.l = false;
		}

		// password

		void	set_password(std::string chanop, std::string key)
		{
			if (key.empty() == true)
				throw std::runtime_error(":Not enough parameters: Code 461");
			if (is_operator(chanop) == false)
				throw std::runtime_error("You're not channel operator: Code 482");
			if (password.empty() == false)
				throw std::runtime_error(":Channel key already set: Code 467");
			password = key;
			mode.k = true;
		}

		void	unset_password(std::string chanop, std::string key)
		{
			if (key.empty() == true)
				throw std::runtime_error(":Not enough parameters: Code 461");
			if (is_operator(chanop) == false)
				throw std::runtime_error("You're not channel operator: Code 482");
			if (key != password)
				throw std::runtime_error(":Channel key already set: Code 467");
			password.erase();
			mode.k = false;
		}

		void	set_invitation(std::string chanop)
		{
			if (is_operator(chanop) == false)
				throw std::runtime_error("You're not channel operator: Code 482");
			mode.i = true;
		}

		void	unset_invitation(std::string chanop)
		{
			if (is_operator(chanop) == false)
				throw std::runtime_error("You're not channel operator: Code 482");
			invitations.clear();
			mode.i = false;
		}

		void	change_topic(std::string nick, std::string topic)
		{
			if (mode.t == true)
			{
				if (is_operator(nick) == false)
					throw std::runtime_error(":You're not channel operator: Code 482");				
			}
			_topic = topic;
		}

		bool	can_speak(std::string nick)
		{
			if (is_user(nick) == true)
			{
				if (is_banned(nick) == true || mode.m == true)
				{
					if (is_operator(nick) == true || is_voice(nick) == true)
						return true;
					return false;
				}
			}
			return true;
		}

		void add_invitation(std::string nick)
		{

		}

};

#endif
