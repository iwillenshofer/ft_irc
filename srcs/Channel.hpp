/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 22:50:49 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/20 19:56:10 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <string>
# include <algorithm>
# include <exception>
# include <stdexcept>
# include <cstring>

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

		Channel(void);
		Channel(std::string name, std::string creator);
		Channel(Channel const &cp);
		Channel &operator=(Channel const &cp);
		virtual ~Channel(void);

		void		set_name(std::string name);
		std::string	get_name(void) const;

		std::string	get_creator(void) const;

		void		set_topic(std::string nick, std::string topic);
		std::string	get_topic(void) const;

		void		set_password(std::string chanop, std::string key);
		void		unset_password(std::string chanop, std::string key);

		bool		get_mode(char mode) const;
		void		activate_mode(std::string nick, char flag, std::string arg);
		void		desactivate_mode(std::string nick, char flag, std::string arg);

		void		set_user_limit(std::string chanop, std::string limit);
		void		unset_user_limit(std::string chanop);

		bool 		is_user(std::string nick);
		void 		add_user(std::string nick);
		void 		remove_user(std::string nick);

		bool		is_operator(std::string nick);
		void		add_operator(std::string chanop, std::string nick);
		void		remove_operator(std::string chanop, std::string nick);

		bool		is_voice(std::string nick);
		void		add_voice(std::string chanop, std::string nick);
		void		remove_voice(std::string chanop, std::string nick);

		bool		is_banned(std::string nick);
		void		add_ban(std::string chanop, std::string nick);
		void		remove_ban(std::string chanop, std::string nick);

		void		set_invitation(std::string chanop);
		void		unset_invitation(std::string chanop);
		bool		is_invitation(std::string nick);
		void		add_invitation(std::string chanop, std::string nick);
		void		remove_invitation(std::string nick);

		void		set_moderated(std::string chanop);
		void		unset_moderated(std::string chanop);

		void		set_no_outside(std::string chanop);
		void		unset_no_outside(std::string chanop);

		void		set_private(std::string chanop);
		void		unset_private(std::string chanop);

		void		set_secret(std::string chanop);
		void		unset_secret(std::string chanop);

		void		set_change_topic(std::string chanop);
		void		unset_change_topic(std::string chanop);

		bool		can_speak(std::string nick);

	public:

		std::vector<std::string> 	users;

	private:

		std::string					_name;
		std::string 				_creator;
		std::string					_topic;
		std::string					_password;
		t_channelmode 				_mode;
		size_t						_user_limit;
		std::vector<std::string> 	_operators;
		std::vector<std::string> 	_voices;
		std::vector<std::string>	_bans;
		std::vector<std::string>	_invitations;
		
};

#endif
