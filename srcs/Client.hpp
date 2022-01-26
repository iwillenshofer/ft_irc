/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roman <roman@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 14:55:35 by iwillens          #+#    #+#             */
/*   Updated: 2022/01/25 22:12:59 by roman            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <cstring>
# include <ctime>
# include "Server.hpp"
# include "server_defaults.hpp"
# include "Commands.hpp"

class Commands;

/*
** user modes. currently a struct, but will be converted into a class so it can initialize itself.
*/
typedef struct s_usermode
{

	bool i;
	bool s;
	bool w;
	bool o;

	bool a; //  not used
	bool r; //  not used
	bool O; //  not used

} t_usermode;

class Client
{
	public:
		Client(int fd = 0);
		Client(Client const &cp);
		Client &operator=(Client const &cp);
		virtual ~Client();
	
	private:
		int									_fd;
		char								_buffer[BUFFERSIZE + 1];
		std::string							_receive_buffer;
		std::string							_send_buffer;
		std::vector<std::string> 			_receive_queue;
		std::vector<std::string> 			_send_queue;
		bool								_hangup;
		std::string							_hangup_message;


	public:
		/*
		** User properties. maybe could become a class...
		** We would also want to set Server Properties, as a static variable
		** (also possibly a class), so it replicates to all clients,
		** allowing us to send just the client to the Commands class,
		** instead of also sending the User and Server properties separately.
		*/
		std::string 				nickname;
		std::string 				username;
		std::string 				hostname;
		std::string 				realname;
		std::string					password;
		bool						registered;
		t_usermode					mode;
		time_t						last_ping;
		bool						is_ping;
		time_t						joined_time;


		/*
		** setters and getters.
		*/
		std::string 				get_prefix(void);
		int			 				get_idle(void);

		size_t 						get_send_queue_size(void);
		std::vector<std::string> 	&get_send_queue(void);
		std::vector<std::string> 	&get_receive_queue(void);
		bool 						get_hangup(void);
		std::string 				&get_hangup_message(void);
		void 						set_hangup(bool v, std::string m = MSG_ENDLINE);
		int 						get_fd(void);
		void 						set_fd(int fd);

		void	activate_mode(char flag);
		void	deactivate_mode(char flag);

		bool	is_invisible(void) const;
		void	set_invisible(void);
		void	unset_invisible(void);

		bool	is_receive_notices(void) const;
		void	set_receive_notices(void);
		void	unset_receive_notices(void);

		bool	is_receive_wallops(void) const;
		void	set_receive_wallops(void);
		void	unset_receive_wallops(void);

		bool	is_operator(void) const;
		void	set_operator(void);
		void	unset_operator(void);

		bool	can_be_operator(std::string nick);
		
		/*
		** reads messages from the client. If message is incomplete,
		** it is kept on buffer to be read on the next poll loop.
		*/

		void read(void);

		/*
		** writes any queued message to client.
		** if message if not fully sent, its remaining is kept on queue to be sent on
		** the next loop.
		*/
	
		void write(void);

		std::string _get_address(void);

		void	init_irc_op(void);
};

#endif
