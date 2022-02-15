/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 22:50:49 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 21:32:38 by iwillens         ###   ########.fr       */
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
# include "Debug.hpp"
# include "Client.hpp"
# include "Message.hpp"
# include "utilities.hpp"
# include "ChannelMode.hpp"

class Channel
{
	public:

		Channel(void);
		Channel(std::string name, Client &creator);
		Channel(Channel const &cp);
		Channel &operator=(Channel const &cp);
		virtual ~Channel(void);

		void		set_name(std::string name);
		std::string	get_name(void) const;

		Client *	get_creator(void) const;

		void		set_topic(Client &nick, std::string topic);
		std::string	get_topic(void) const;

		bool		match_password(unsigned long password) const;
		void		set_password(Client &chanop, unsigned long key);
		void		unset_password(Client &chanop, unsigned long key);

		std::string	get_modes(void) const;
		std::string	get_mode_params(void) const;
		bool		get_mode(char mode) const;
		void		activate_mode(Client &nick, char flag, std::string arg = "", Client *target = NULL);
		void		deactivate_mode(Client &nick, char flag, std::string arg = "", Client *target = NULL);

		void		set_user_limit(Client &chanop, std::string limit);
		void		unset_user_limit(Client &chanop);

		bool 		is_user(Client &nick);
		void 		add_user(Client &nick, unsigned long password = START_HASH);
		void 		remove_user(Client &nick);

		bool		is_operator(Client &nick);
		void		add_operator(Client &chanop, Client *nick);
		void		remove_operator(Client &chanop, Client *nick);

		bool		is_voice(Client &nick);
		void		add_voice(Client &chanop, Client *nick);
		void		remove_voice(Client &chanop, Client *nick);

		std::vector<std::string>	&get_ban_list(void);
		bool		is_banned(Client &client);
		bool		is_banned(std::string mask);
		void		add_ban(Client & chanop, std::string mask);
		void		remove_ban(Client & chanop, std::string mask);

		bool		is_invitation_only(void) const;
		void		set_invitation(Client &chanop);
		void		unset_invitation(Client &chanop);
		bool		is_invitation(Client &nick);
		void		add_invitation(Client &chanop, Client &nick);
		void		add_invitation(Client &nick);
		void		remove_invitation(Client &nick);

		bool		is_moderated(void);
		void		set_moderated(Client &chanop);
		void		unset_moderated(Client &chanop);

		bool		is_no_outside(void);
		void		set_no_outside(Client &chanop);
		void		unset_no_outside(Client &chanop);

		bool		is_private(void);
		void		set_private(Client &chanop);
		void		unset_private(Client &chanop);

		bool		is_secret(void);
		void		set_secret(Client &chanop);
		void		unset_secret(Client &chanop);

		void		set_change_topic(Client &chanop);
		void		unset_change_topic(Client &chanop);

		bool		can_speak(Client &nick);

		void		change_nick(Client &oldnick, Client &newnick);

		bool		is_empty(void);

	public:

		std::vector<Client *> 	users;

	private:

		std::string					_name;
		Client 						*_creator;
		std::string					_topic;
		unsigned long				_password;
		ChannelMode 				_mode;
		size_t						_user_limit;
		std::vector<Client *>	 	_operators;
		std::vector<Client *>	 	_voices;
		std::vector<std::string>	_bans;
		std::vector<Client *>		_invitations;
		
};

#endif
