/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:01:32 by romanbtt          #+#    #+#             */
/*   Updated: 2022/01/09 09:30:33 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.hpp"

std::string ft::left_trim( const std::string& str )
{
    size_t start = str.find_first_not_of(' ');

	if (start == std::string::npos)
		return ("");
	else
		return str.substr(start);
}
 
std::string ft::right_trim( const std::string& str )
{
    size_t end = str.find_last_not_of(' ');

	if (end == std::string::npos)
		return ("");
	else
		return str.substr(0, end + 1);
}
 
std::string ft::trim( const std::string& str )
{
    return right_trim(left_trim(str));
}

void ft::trimString(std::string& str)
{
	str.erase(str.find_last_not_of(' ') + 1);
    str.erase(0, str.find_first_not_of(' '));
}

bool ft::isNumeric(std::string& s)
{
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
		if (!(std::isdigit(*it)))
			return (false);
	return (true);
}

std::string ft::getHostByName(std::string s)
{
	struct hostent *host;

	host = gethostbyname(s.c_str());
	if (host == NULL)
		return(std::string());
	return(std::string(inet_ntoa(*(struct in_addr*)host->h_addr)));
}

std::vector<std::string> ft::split(const std::string &s, char separator)
{
	std::vector<std::string> items;
	std::string::size_type start = 0;
	std::string::size_type end = 0;

	while ((end = s.find(separator, start)) != std::string::npos)
	{
		items.push_back(s.substr(start, end - start));
		start = end + 1;
	}
	items.push_back(s.substr(start));
	return items;
}

std::string ft::get_str_between_two_str(const std::string &s,
        const std::string &start_delim,
        const std::string &stop_delim)
{
    unsigned first_delim_pos = s.find(start_delim);
    unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
    unsigned last_delim_pos = s.find_first_of(stop_delim, end_pos_of_first_delim);
    
    return s.substr(end_pos_of_first_delim,
            last_delim_pos - end_pos_of_first_delim);
}

std::string	ft::get_current_date( void )
{
	time_t rawtime;
	struct tm* timeinfo;
	char output[30];

	time (&rawtime);
	timeinfo = gmtime(&rawtime);
	strftime(output, 30, "%a, %d %b %Y %X %Z", timeinfo);
	
	return std::string(output);
}
