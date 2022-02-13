/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 20:52:59 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/12 21:28:55 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
# define TESTER_HPP

# include <vector>
# include "IrcClient.hpp"
# include "Debug.hpp"

# define LINE_WIDTH 80

class Tester
{
	public:
		Tester(std::string host, int port, std::string password);
		Tester(Tester const &cp);
		Tester &operator=(Tester const &cp);
		virtual ~Tester();

		std::string 	_host;
		int				_port;
		std::string		_password;

		/*
		** tester helper functions
		*/

	private:
		Tester(void);
		std::vector<std::string> _break_line(std::string s);
			
	public:
		void title(std::string s);
		void description(std::string s);
		void perform_tests(void);


		/*
		** tests admin
		*/
		void test_admin(void);

		/*
		** tests connect
		*/
		void test_connect(void);

		/*
		** tests error
		*/
		void test_error(void);

		/*
		** tests info
		*/
		void test_info(void);

		/*
		** tests invite
		*/
		void test_invite(void);

		/*
		** tests join
		*/
		void test_join(void);

		/*
		** tests kick
		*/
		void test_kick(void);

		/*
		** tests kill
		*/
		void test_kill(void);

		/*
		** tests links
		*/
		void test_links(void);

		/*
		** tests list
		*/
		void test_list(void);

		/*
		** tests lusers
		*/
		void test_lusers(void);

		/*
		** tests mode_channel
		*/
		void test_mode_channel(void);

		/*
		** tests mode_user
		*/
		void test_mode_user(void);

		/*
		** tests motd
		*/
		void test_motd(void);

		/*
		** tests names
		*/
		void test_names(void);

		/*
		** tests nick
		*/
		void test_nick(void);

		/*
		** tests notice
		*/
		void test_notice(void);

		/*
		** tests oper
		*/
		void test_oper(void);

		/*
		** tests part
		*/
		void test_part(void);

		/*
		** tests pass
		*/
		void test_pass(void);

		/*
		** tests ping
		*/
		void test_ping(void);

		/*
		** tests pong
		*/
		void test_pong(void);

		/*
		** tests privmsg
		*/
		void test_privmsg(void);

		/*
		** tests quit
		*/
		void test_quit(void);

		/*
		** tests server
		*/
		void test_server(void);

		/*
		** tests squit
		*/
		void test_squit(void);

		/*
		** tests stats
		*/
		void test_stats(void);

		/*
		** tests time
		*/
		void test_time(void);

		/*
		** tests topic
		*/
		void test_topic(void);

		/*
		** tests trace [done]
		*/
		void test_trace(void);
		void test_trace_server(void);
		/*
		** tests user [done]
		*/
		void test_user(void);
		void test_user_parameters(void);

		/*
		** tests version [done]
		*/
		void test_version(void);

		/*
		** tests registration [done]
		*/
		void test_registration(void);
		void test_registration_full(void);
		void test_registration_invalid_password(void);
		void test_registration_command(void);
		void test_registration_nicknameinuse(void);
		void test_registration_nicknameinuse_retry(void);
		void test_registration_timeout(void);

		/*
		** tests whois [done]
		*/
		void test_whois(void);
		void test_whois_invalidusername(void);
		void test_whois_visibility(void);
		void test_whois_no_parameters(void);
		void test_whois_masks(void);
		void test_whois_misc(void);
		void test_whois_samechannel(void);
		
		/*
		** tests whowas [done]
		*/
		void test_whowas(void);
		void test_whowas_no_parameters(void);
		void test_whowas_invalidusername(void);
		void test_whowas_clients(void);

		/*
		** tests who [done]
		*/
		void test_who(void);
		void test_who_masks(void);
		void test_who_channel(void);

};

#endif