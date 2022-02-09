/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:01:32 by romanbtt          #+#    #+#             */
/*   Updated: 2022/02/09 19:49:20 by iwillens         ###   ########.fr       */
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

std::vector<std::string> ft::split(std::string &s, std::string separator)
{
	std::string item;
	std::vector<std::string> items;
	std::string::size_type pos = 0;
	
	while ((pos = s.find(separator)) != std::string::npos)
	{
		items.push_back(s.substr(0, pos));
		s.erase(0, pos + separator.length());
	}
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

	time (&rawtime);
	return std::string(format_date(rawtime));
}

std::string	ft::format_date( time_t rawtime )
{
	struct tm* timeinfo;
	char output[30];

	timeinfo = gmtime(&rawtime);
	strftime(output, 30, "%a, %d %b %Y %X %Z", timeinfo);
	
	return std::string(output);
}

void ft::uppercase(std::string &s)
{
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
		*it = std::toupper(*it);
}

std::string ft::load_file(std::string filename)
{
	struct stat attributes;
	std::string file;

	if (stat(filename.c_str(), &attributes))
		throw std::runtime_error("File '" + filename + "' does not exist.");
	std::ifstream ifs(filename.c_str());
	if (ifs.fail())
	{
		ifs.close();
		throw std::runtime_error("File '" + filename + "' could not be open.");
	}
	file = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
	ifs.close();
	return (file);
}

unsigned long ft::hash(const char *str)
{
    unsigned long	hash = START_HASH;
    int 			c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

void ft::replace_string(std::string &s, std::string find, std::string replace)
{
	while (s.find(find) != std::string::npos)
		s.replace(s.find(find), find.size(), replace);
}
