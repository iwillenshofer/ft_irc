/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:02:23 by romanbtt          #+#    #+#             */
/*   Updated: 2022/02/08 22:42:18 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
# define UTILITIES_HPP

# include <string>
# include <string>
# include <vector>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sstream>
# include <ctime>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fstream>
# include <server_defaults.hpp>

namespace ft
{
	std::string left_trim( const std::string& str );
	std::string right_trim( const std::string& str );
	std::string trim( const std::string& str );

	void trimString(std::string& str);
	bool isNumeric(std::string& s);
	std::string getHostByName(std::string s);
	std::vector<std::string> split(const std::string &s, char separator);
	std::vector<std::string> split(std::string &s, std::string separator);

	template<typename T>
	std::string to_string(const T& value)
	{
		std::ostringstream oss;
		oss << value;
		return (oss.str());
	}
	
	void uppercase(std::string &s);

	std::string get_str_between_two_str(const std::string &s,
        const std::string &start_delim,
        const std::string &stop_delim);

	std::string	get_current_date( void );
	std::string	format_date( time_t rawtime );
	std::string load_file(std::string filename);
	unsigned long hash(const char *str);
}

#endif
