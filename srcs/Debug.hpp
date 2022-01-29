/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Debug.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:10:11 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/28 23:15:36 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_HPP
# define DEBUG_HPP

# include <iostream>
# include "utilities.hpp"

# define CLR_BLACK			30
# define CLR_RED			31
# define CLR_GREEN			32
# define CLR_YELLOW			33
# define CLR_BLUE			34
# define CLR_MAGENTA		35
# define CLR_CYAN			36
# define CLR_WHITE			37

# define CLR_DEFAULT		0
# define CLR_BOLD			1
# define CLR_DIM			2
# define CLR_ITALICS		3
# define CLR_UNDERLINED		4
# define CLR_BLINK			5
# define CLR_REVERSE		7
# define CLR_HIDDEN			8
# define CLR_LIGHTFG		16
# define CLR_LIGHTBG		32

# define DBG_DEV			0
# define DBG_INFO			1
# define DBG_WARNING		2
# define DBG_ERROR			3
# define DBG_FATAL			4

# define DBG_DEFAULT		DBG_INFO

/*
** Debug Class
** Will print to std::cout according to the debug level set by the application.
** Defautl Level: DBG_INFO.
** To set the _debug_level, call the set_level static function as follows:
**  Debug::set_level(DBG_WARNING);
** Any message below the _debug_level will be ignored.
** To print a debug message just call: Debug("message", DBG_INFO);
** available levels: DBG_INFO, DBG_WARNING, DBG_ERROR, DBG_DEV
** DBG_DEV must be used for checkpoints. Will make it easier to find
**  and remove these lines when deploying.
*/

class Debug
{	

	public:
		Debug();
		Debug(Debug const &c);
		Debug(std::string s, int level = DBG_INFO);
		virtual ~Debug();
		Debug &operator=(Debug const &c);
		static void set_level(int level);
		std::string					get_title(bool show_color = true);

	private:
		std::string 				_text;
		int							_msg_level;
		static int					_debug_level;
		std::string					_get_date(void);
		std::string					_get_text(void);
		std::string					_reset_color(void);
		void						_print();
};

#endif
