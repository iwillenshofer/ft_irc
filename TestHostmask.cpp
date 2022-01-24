/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestHostmask.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:08:12 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/23 21:54:08 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./srcs/Mask.hpp"

int main (int argc, char *argv[])
{
	Debug::setLevel(DBG_DEV);
	
	if (argc == 2)
		Debug(std::string("Result: ") + Mask::create(std::string(argv[1])));
	else if (argc == 3)
		Debug(std::string("Result: ") + (Mask::match_raw(std::string(argv[1]), std::string(argv[2])) ? "TRUE" : "FALSE"));
	else
	{
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefg", "abcdefg")           == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefg", "aacdefg")           == 0 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefg", "*cde*")             == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefg", "cde*")              == 0 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefg", "*cde")              == 0 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdfcdefg", "**cde")          == 0 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdfcdefg", "**cde*")         == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdexxxcdefg", "*cdef*cdef")  == 0 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcxxdexxxcdefg", "*xxx*?g")   == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdexxxcdefg", "*cdef*cdef*") == 0 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefg", "*cdf*cdef*")        == 0 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefg", "*")                 == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("", "*")                        == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("d", "?")                       == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("ddd", "*?")                    == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("ddd", "?*")                    == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("ddd", "???")                   == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("ddd", "*?*")                   == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("", "?")                        == 0 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefg", "*?cde*")            == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefg", "??cde??")           == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefg", "??cde?")            == 0 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefg", "ppppp")             == 0 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefg", "??c??")             == 0 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefxxxcdefg", "*cdef*cdef?") == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefxxxcdefg", "*cdef*cdef*") == 1 ? "TRUE" : "FALSE"));
    	Debug(std::string("Result: ") + (Mask::match_raw("abcdefxxxcdefg", "*cdef*cdef") == 0 ? "TRUE" : "FALSE"));
	}
}