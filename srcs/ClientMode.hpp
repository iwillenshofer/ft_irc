/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 21:22:26 by iwillens          #+#    #+#             */
/*   Updated: 2022/02/14 21:25:22 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTMODE_HPP
# define CLIENTMODE_HPP

/*
** user modes. currently a struct, but will be converted into a class so it can initialize itself.
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

		bool r; //  not used
		bool O; //  not used
};

#endif
