/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDescriptorAttributes.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:24:05 by iwillens          #+#    #+#             */
/*   Updated: 2021/12/05 10:13:04 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEDESCRIPTORATTRIBUTES_HPP
# define FILEDESCRIPTORATTRIBUTES_HPP

# include <ctime>
# include "Bind.hpp"
# include "../parser/ContextBase.hpp"
# include "../request/Request.hpp"
# define DFL_TIMEOUT 3

# define FDKIND_SOCKET	1
# define FDKIND_ACCEPT	2
# define FDKIND_CGI		3

class Bind;

class FileDescriptorAttributes
{
	public:
		FileDescriptorAttributes(Bind *bind = NULL, int kind = FDKIND_SOCKET);
		FileDescriptorAttributes(FileDescriptorAttributes const &cp);
		FileDescriptorAttributes &operator=(FileDescriptorAttributes const &cp);
		virtual ~FileDescriptorAttributes();

	private:
		std::string				_content;
		struct timespec			_createdTime;
		DefaultType<Request>	_header;
//		DefaultType<Responset>	_response;
		DefaultType<long>		_expectedRecvSize;
		DefaultType<long>		_receivedSize;
		DefaultType<long>		_expectedSendSize;
		DefaultType<long>		_sentSize;
		DefaultType<bool>		_cgiReady;
		int						_kind;

		/*
		** read properties
		*/
		bool					_should_close; //marks fd to close at the end of the loop
		bool					_one_shot; // will give one try if fd is open
		size_t					_header_error; // an error occurred in header
		bool					_socket_error; // an error occurred when reading socket
		bool					_completed_content; // content has been read completely
		ssize_t					_kernel_available;
		Bind					*_bind;

	
	public:
		DefaultType<long>		&getExpectedRecvSize();
		DefaultType<long>		&getReceivedSize();
		DefaultType<long>		&getExpectedSendSize();
		DefaultType<long>		&getSentSize();
		bool					getShouldClose();
		Bind					*getBind();
		DefaultType<Request>	&getHeader();
		DefaultType<bool>		&cgiReady();
		DefaultType<bool>		&cgiReady(bool val);



		void		setExpectedRecvSize(long val);
		void		setReceivedSize(long val);
		void		setExpectedSendSize(long val);
		void		setSentSize(long val);
		void		setBind(Bind *bind);
		void		setContent(char *str);
		void		setContent(std::string str);
		void		setHeader(std::string &str);
		void		addContent(char *str);
		std::string &getContent(void);
		bool		timedOut(void);
		int			getKind(void);
		/*
		** read methods
		*/
		bool		shouldClose(bool);
		bool		shouldClose(void);
		bool		oneShot(void);
		bool		oneShot(bool);
		size_t		headerError(void);
		size_t		headerError(size_t);
		bool		socketError(void);
		bool		socketError(bool);
		bool		completedContent(void);
		bool		completedContent(bool);
		ssize_t		kernelAvailable(void);
		ssize_t		kernelAvailable(ssize_t);
};

#endif
