/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:23:01 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/14 19:21:52 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::map<std::string, Commands::cmd_type> Commands::initFunction(void)
{
	std::map<std::string, Commands::cmd_type> cmd;

	cmd["NICK"] = &Commands::_cmd_nick;
	cmd["USER"] = &Commands::_cmd_user;
	cmd["MOTD"] = &Commands::_cmd_motd;
	cmd["PONG"] = &Commands::_cmd_pong;

	return (cmd);
}

std::map<std::string, Commands::cmd_type> Commands::_commands = initFunction();
