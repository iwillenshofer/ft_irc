/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:47:11 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/31 15:11:19 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>
# include <algorithm>
# include "Debug.hpp"
# include "server_defaults.hpp"

class Message
{
	public:
		Message(void);
		Message(std::string message);
		Message(Message const &cp);
		Message &operator=(Message const &cp);
		virtual ~Message();
		
	private:
		std::string						_message;
		std::string						_prefix;
		std::string						_command;
		std::vector<std::string>		_arguments;

	public:
		/*
		** getters
		*/
		std::string					&message(void);
		std::string					&prefix(void);
		std::string					&command(void);
		std::vector<std::string>	&arguments(void);
		
	private:
		/*
		** disassembles _message into _prefix, _command and [_arguments]
		*/
		
		void _disassemble(void);
		void _validate(void);

	public:	
		void print(void);

		/*
		** Static functions to validate strings/chars according to RFC2812 Section-2.3.1
		** Message format in Augmented BNF
		** https://datatracker.ietf.org/doc/html/rfc2812#section-2.3.1
		*/

		static bool is_bnf_target(std::string const &key);
		static bool is_bnf_msgtarget(std::string const &key);
		static bool is_bnf_msgto(std::string const &key);
		static bool is_bnf_channel(std::string const &key);
		static bool is_bnf_servername(std::string const &key);
		static bool is_bnf_host(std::string const &key);
		static bool is_bnf_hostname(std::string const &key);
		static bool is_bnf_shortname(std::string const &key);
		static bool is_bnf_hostaddr(std::string const &key);
		static bool is_bnf_ipv4addr_mask(std::string const &key);
		static bool is_bnf_ipv4addr(std::string const &key);
		static bool is_bnf_ipv6addr(std::string const &key);
		static bool is_bnf_nickname(std::string const &nickname);

		/*
		** Responses:
		**  BNF_TARGETMSK_INVALID
		**  BNF_TARGETMSK_VALID
		**  BNF_TARGETMSK_NOTOPLEVEL
		**  BNF_TARGETMSK_WILDTOPLEVEL
		*/

		static int is_bnf_targetmask(std::string const &key);
		static bool is_bnf_mask(std::string const &key);
		static bool is_bnf_chanstring(std::string const &key);
		static bool is_bnf_channelid(std::string const &key);
		static bool is_bnf_user(std::string const &key);
		static bool is_bnf_key(std::string const &key);
		static bool is_bnf_letter(const char c);
		static bool is_bnf_digit(const char c);
		static bool is_bnf_hexdigit(const char c);
		static bool is_bnf_special(const char c);

		/*
		** string functions
		*/
		static void clear_commas(std::string &s);
		static void remove_double_commas(std::string &s);
		static std::vector<std::string> split_commas(std::string s, bool trim_commas = true);
		
		class InputLineTooLong : public std::exception { virtual const char* what() const throw(); };
		class EmptyMessage : public std::exception { virtual const char* what() const throw(); };
};


#endif
