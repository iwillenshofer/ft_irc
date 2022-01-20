/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:47:11 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/19 23:11:25 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>
# include "Debug.hpp"
# include "server_defaults.hpp"

class Message
{
	public:
		Message(void) { };
		Message(std::string message): _message(message)
		{
			_disassemble();
			_validate();
		}
		Message(Message const &cp) { *this = cp; }
		Message &operator=(Message const &cp)
		{
			_message = cp._message;
			_prefix = cp._prefix;
			_command = cp._command;
			_arguments = cp._arguments;
			return (*this);
		}
		virtual ~Message() { };
	
	
	private:
		std::string						_message;
		std::string						_prefix;
		std::string						_command;
		std::vector<std::string>		_arguments;

	public:
		/*
		** getters
		*/
		std::string					&message(void) {return (_message); }
		std::string					&prefix(void) {return (_prefix); }
		std::string					&command(void) {return (_command); }
		std::vector<std::string>	&arguments(void) {return (_arguments); }
		
	private:
		/*
		** disassembles _message into _prefix, _command and [_arguments]
		*/
		void _disassemble(void)
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
			_arguments.push_back(user_message);
			ft::uppercase(_command);
		}

		void _validate(void)
		{
			if (_message.size() > MSG_MAXMSGSIZE)
				throw InputLineTooLong();
			if (!(_message.size()) || !(_command.size()))
				throw EmptyMessage();
		}
	
	public:
		void print(void)
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
		** Static functions to validate strings/chars according to RFC2812 Section-2.3.1
		** Message format in Augmented BNF
		** https://datatracker.ietf.org/doc/html/rfc2812#section-2.3.1
		*/

		static bool validate_bnf_channel(std::string const &key)
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
				if (!(validate_bnf_channelid(key.substr(1, 5))))
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
				if (!validate_bnf_chanstring(*it))
					return (false);
			return (true);
		}

		static bool validate_bnf_servername(std::string const &key)
		{
			if (validate_bnf_host(key))
				return (true);
			return (false);
		}
		
		static bool validate_bnf_host(std::string const &key)
		{
			if (validate_bnf_hostname(key) || validate_bnf_hostaddr(key))
				return (true);
			return (false);
		}

		static bool validate_bnf_hostname(std::string const &key)
		{
			std::vector<std::string> v;
			if (!(key.size()))
				return (false);
			if (key.find("..") != std::string::npos || key[0] == '.' || key[key.size() - 1] == '.')
				return (false);
			v = ft::split(key, '.');
			for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
				if (!(validate_bnf_shortname(*it)))
					return (false);
			return (true);
		}

		static bool validate_bnf_shortname(std::string const &key)
		{
			if (!(key.size()))
				return (false);
			if (!(validate_bnf_letter(key[0])) && !(validate_bnf_digit(key[0])))
				return (false);
			for (std::string::const_iterator it = key.begin(); it != key.end(); it++)
				if (!(validate_bnf_letter(*it)) && !(validate_bnf_digit(*it)) && *it != '-')
					return (false);
			if (key[key.size() - 1] == '-')
				return (false);
			return (true);
		}

		static bool validate_bnf_hostaddr(std::string const &key)
		{
			if (validate_bnf_ipv4addr(key) || validate_bnf_ipv6addr(key))
				return (true);
			return (false);
		}

		static bool validate_bnf_ipv4addr(std::string const &key)
		{
			(void)key;
			/*
			** TO-DO
			*/
		}

		static bool validate_bnf_ipv6addr(std::string const &key)
		{
			(void)key;
			/*
			** TO-DO
			*/
		}

		static bool validate_bnf_nickname(std::string const &nickname)
		{
			if (!(nickname.size()) || nickname.size() > SRV_MAXNICKLEN)
				return (false);
			if (!(validate_bnf_letter(nickname[0])) && !(validate_bnf_special(nickname[0])))
				return (false);
			for (std::string::const_iterator it = nickname.begin(); it != nickname.end(); it++)
				if (!(validate_bnf_letter(*it)) && !(validate_bnf_special(*it)
				&& !(validate_bnf_digit(*it)) && *it != '-'))
					return (false);
			return (true);
		}

		static bool validate_bnf_targetmask(std::string const &key)
		{
			(void)key;
			/*
			** TO-DO
			*/
		}

		static bool validate_bnf_chanstring(std::string const &key)
		{
			std::string s(MSG_BNF_CHANNELSTRFORBIDDEN);

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

		static bool validate_bnf_channelid(std::string const &key)
		{
			if (key.size() != MSG_BNF_CHANNELIDSIZE)
				return (false);
			for (std::string::const_iterator it = key.begin(); it != key.end(); it++)
			{
				if (!(validate_bnf_digit(*it)) || *it < 'A' || *it > 'Z')
					return (false);
			}
			return (true);
		}

		static bool validate_bnf_user(std::string const &key)
		{
			std::string s(MSG_BNF_USERFORBIDDEN);

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

		static bool validate_bnf_key(std::string const &key)
		{
			std::string s(MSG_BNF_KEYFORBIDDEN);

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

		static bool validate_bnf_letter(const char c)
		{
			std::string s(MSG_BNF_LETTER);

			for (std::string::iterator it = s.begin(); it != s.end(); it++)
				if (*it == c)
					return (true);
			return (false);
		}


		static bool validate_bnf_digit(const char c)
		{
			std::string s(MSG_BNF_DIGIT);

			for (std::string::iterator it = s.begin(); it != s.end(); it++)
				if (*it == c)
					return (true);
			return (false);
		}

		static bool validate_bnf_hexdigit(const char c)
		{
			std::string s(MSG_BNF_HEXDIGIT);

			if (validate_bnf_digit(c))
				return (true);
			for (std::string::iterator it = s.begin(); it != s.end(); it++)
				if (*it == c)
					return (true);
			return (false);
		}

		static bool validate_bnf_special(const char c)
		{
			std::string s(MSG_BNF_LETTER);

			for (std::string::iterator it = s.begin(); it != s.end(); it++)
				if (*it == c)
					return (true);
			return (false);
		}






		struct InputLineTooLong : public std::exception
		{
				virtual const char*	what() const throw() { return ("417: Input line was too long."); }
		};

		struct EmptyMessage : public std::exception
		{
				virtual const char*	what() const throw() { return ("Empty Message."); }
		};
};


#endif
