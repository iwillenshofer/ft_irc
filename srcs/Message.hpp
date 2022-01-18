/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:47:11 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/18 17:50:11 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <string>
# include <vector>
# include "Debug.hpp"

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
