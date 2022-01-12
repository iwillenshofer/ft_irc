/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 22:50:49 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/11 23:24:19 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <string>

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
		Channel(void) { }
		Channel(Channel const &cp) { *this = cp; }
		Channel &operator=(Channel const &cp)
		{
			mode = cp.mode;

			return (*this);
		}
		virtual ~Channel() { };
	
	private:
		t_channelmode 				mode;
		std::string 				creator;
		std::vector<std::string> 	users;
		std::vector<std::string> 	operators;
		std::vector<std::string> 	voices;
		int							user_limit;
		std::string					channel_key;
		std::vector<std::string>	bans;
		std::vector<std::string>	invitations;


	public:
		bool find_user(std::string nick)
		{
			for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); it++)
				if (*it == nick)
					return true;
			return (false);
		}
		
		bool add_user(std::string nick) { users.push_back(nick); }

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

};

#endif
