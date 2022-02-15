/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 21:22:23 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 21:38:30 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelMode.hpp"

/*
** ChannelMode
*/

ChannelMode::ChannelMode(void)
: O(false), o(false), v(false), a(false), i(false), m(false), n(false),
	q(false), p(false), s(false), r(false), t(false), k(false),
	l(false), b(false), e(false), I(false)
{ }
ChannelMode::ChannelMode(ChannelMode const &cp) { *this = cp; }
ChannelMode &ChannelMode::operator=(ChannelMode const &cp)
{
	O = cp.O;
	o = cp.o;
	v = cp.v;
	a = cp.a;
	i = cp.i;
	m = cp.m;
	n = cp.n;
	q = cp.q;
	p = cp.p;
	s = cp.s;
	r = cp.r;
	t = cp.t;
	k = cp.k;
	l = cp.l;
	b = cp.b;
	e = cp.e;
	I = cp.I;
	return (*this);
}

ChannelMode::~ChannelMode() { }
