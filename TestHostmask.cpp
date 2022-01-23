/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestHostmask.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:08:12 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/23 15:06:44 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./srcs/Mask.hpp"

int main (int argc, char *argv[])
{
	Debug::setLevel(DBG_DEV);
	
	if (argc == 2)
		Debug(std::string("Result: ") + Mask::create(std::string(argv[1])));
	else if (argc == 3)
		Debug(std::string("Result: ") + (Mask::match(std::string(argv[1]), std::string(argv[2])) ? "TRUE" : "FALSE"));
}