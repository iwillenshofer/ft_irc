/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:23:01 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/13 13:14:21 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::map<std::string, Commands::cmd_type> Commands::initFunction(void)
{
	std::map<std::string, Commands::cmd_type> cmd;

	cmd["NICK"] = &Commands::_cmd_nick;
	cmd["USER"] = &Commands::_cmd_user;
	cmd["MOTD"] = &Commands::_cmd_motd;
	return (cmd);
}

std::map<std::string, Commands::cmd_type> Commands::_commands = initFunction();
