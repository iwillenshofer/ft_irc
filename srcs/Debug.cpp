/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:10:09 by iwillens          #+#    #+#             */
/*   Updated: 2021/11/29 09:46:12 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Debug.hpp"

int Debug::_debug_level = DBG_INFO;

Debug::Debug(void) { }

Debug::Debug(Debug const &c) { *this = c; }

Debug::Debug(std::string s, int level)
: _text(s), _msg_level(level) {	_print(); }

Debug::~Debug() { }

Debug &Debug::operator=(Debug const &c)
{
	this->_text = c._text;
	this->_msg_level = c._msg_level;
	return (*this);
}

std::string Debug::_resetColor(void)
{
	std::string str("\033[0m");
	return (str);
}

std::string Debug::_getTitle(void)
{
	std::string str("\033[");
	std::string title;
	int color;
	if (_msg_level == DBG_INFO)
	{
		title = "INFO";
		color = CLR_CYAN;
	}
	else if (_msg_level == DBG_WARNING)
	{
		title = "WARNING";
		color = CLR_YELLOW;
	}
	else if (_msg_level == DBG_ERROR)
	{
		title = "ERROR";
		color = CLR_RED;
	}
	else if (_msg_level == DBG_DEV)
	{
		title = "DEV";
		color = CLR_GREEN;
	}
	else if (_msg_level == DBG_FATAL)
	{
		title = "FATAL ERROR";
		color = CLR_MAGENTA;
	}
	str += ft::to_string(CLR_BOLD) +  ";";
	str += ft::to_string(color) + "m";
	str += "[" + title + "]";
	str += _resetColor();
	return (str);
}

std::string Debug::_getDate(void)
{
	std::string str("\033[");
	std::string title;

	str += ft::to_string(CLR_BOLD) +  ";";
	str += ft::to_string(CLR_WHITE) + "m";
	str += ft::get_current_date();
	str += _resetColor();
	return (str);
}

std::string Debug::_getText(void)
{
	std::string str("\033[");

	str += ft::to_string(CLR_UNDERLINED) +  ";";
	str += ft::to_string(CLR_WHITE) + "m";
	str += _text;
	str += _resetColor();
	return (str);
}

void Debug::_print()
{
	if (_msg_level < _debug_level)
		return ;
	std::cout << _getDate() << " " <<  _getTitle() << " " << _getText() << std::endl << std::flush;
}

void Debug::setLevel(int level)
{
	_debug_level = level;
}
