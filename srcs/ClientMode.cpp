/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 21:22:23 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/16 22:04:19 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientMode.hpp"

/*
** ClientMode
*/

ClientMode::ClientMode(void): i(false), s(false), w(false), o(false), a(false) { }
ClientMode::ClientMode(ClientMode const &cp) { *this = cp; }
ClientMode &ClientMode::operator=(ClientMode const &cp)
{
	i = cp.i;
	s = cp.s;
	w = cp.w;
	o = cp.o;
	a = cp.a;
	return (*this);
}
ClientMode::~ClientMode() { }
