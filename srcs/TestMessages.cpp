/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestMessages.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:02:08 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/20 18:18:22 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/Message.hpp"
#include <iostream>

void title(std::string s)
{
	std::cout << s << std::endl;
}

void assert(bool(*fn)(const std::string &), std::string s, bool b)
{
    bool result = fn(s);
    std::cout << (result == b ? "\x1B[1;32m" : "\x1B[1;31m") << s << "\033[0m\t\t";
}

int main (void)
{
	assert(Message::is_bnf_channel, "#channel", true);

    std::cout << std::endl;
	return 1 ;
}