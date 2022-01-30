/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:10:09 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/30 12:42:53 by iwillens         ###   ########.fr       */
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

std::string Debug::debug_level(void)
{
	if (_debug_level == DBG_INFO)
		return("INFO");
	else if (_debug_level == DBG_WARNING)
		return("WARNING");
	else if (_debug_level == DBG_ERROR)
		return("ERROR");
	else if (_debug_level == DBG_DEV)
		return("DEV");
	else if (_debug_level == DBG_FATAL)
		return("FATAL ERROR");
	return ("");
}

std::string Debug::_reset_color(void)
{
	std::string str("\033[0m");
	return (str);
}

std::string Debug::_get_title(void)
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
	str += _reset_color();
	return (str);
}

std::string Debug::_get_date(void)
{
	std::string str("\033[");
	std::string title;

	str += ft::to_string(CLR_BOLD) +  ";";
	str += ft::to_string(CLR_WHITE) + "m";
	str += ft::get_current_date();
	str += _reset_color();
	return (str);
}

std::string Debug::_get_text(void)
{
	std::string str("\033[");

	str += ft::to_string(CLR_UNDERLINED) +  ";";
	str += ft::to_string(CLR_WHITE) + "m";
	str += _text;
	str += _reset_color();
	return (str);
}

void Debug::_print()
{
	if (_msg_level < _debug_level)
		return ;
	std::cout << _get_date() << " " <<  _get_title() << " " << _get_text() << std::endl << std::flush;
}

void Debug::set_level(int level)
{
	_debug_level = level;
}
