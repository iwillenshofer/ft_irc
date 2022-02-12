/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 20:52:59 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/12 18:26:48 by iwillens         ###   ########.fr       */
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
		std::vector<std::string> _break_line(std::string s);
			
	public:
		void title(std::string s);
		void description(std::string s);
		void perform_tests(void);

		/*
		** tests registration
		*/
		void test_registration(void);
		void test_registration_full(void);
		void test_registration_invalid_password(void);
		void test_registration_command(void);
		void test_registration_nicknameinuse(void);
		void test_registration_nicknameinuse_retry(void);
		void test_registration_timeout(void);

		/*
		** tests whois
		*/
		void test_whois(void);
		void test_whois_invalidusername(void);
		void test_whois_visibility(void);
		void test_whois_no_parameters(void);
		void test_whois_masks(void);
		void test_whois_misc(void);
		void test_whois_samechannel(void);

		void test_whowas(void);
		void test_whowas_no_parameters(void);
		void test_whowas_invalidusername(void);
		void test_whowas_clients(void);

		void test_who(void);
		void test_who_masks(void);
		void test_who_channel(void);

};

#endif
