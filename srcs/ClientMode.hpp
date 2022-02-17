/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 21:22:26 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/16 22:04:43 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTMODE_HPP
# define CLIENTMODE_HPP

/*
** user modes.
*/
class ClientMode
{
	public: 
		ClientMode(void);
		ClientMode(ClientMode const &cp);
		ClientMode &operator=(ClientMode const &cp);
		virtual ~ClientMode();

		bool i;
		bool s;
		bool w;
		bool o;
		bool a;
};

#endif
