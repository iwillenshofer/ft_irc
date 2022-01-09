/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDescriptorAttributes.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillens <iwillens@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:42:03 by iwillens          #+#    #+#             */
/*   Updated: 2021/12/05 10:09:06 by iwillens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileDescriptorAttributes.hpp"

FileDescriptorAttributes::FileDescriptorAttributes(Bind *bind, int kind):
_kind(kind), _should_close(false), _one_shot(false), _header_error(false), _socket_error(false), _completed_content(false), _kernel_available(0), _bind(bind)
{
	clock_gettime(CLOCK_MONOTONIC, &_createdTime);
}

FileDescriptorAttributes::FileDescriptorAttributes(FileDescriptorAttributes const &cp) { *this = cp; }
FileDescriptorAttributes &FileDescriptorAttributes::operator=(FileDescriptorAttributes const &cp)
{
	_kind = cp._kind;
	_content = cp._content;
	_createdTime = cp._createdTime;
	_header = cp._header;
	_expectedRecvSize = cp._expectedRecvSize;
	_receivedSize = cp._receivedSize;
	_expectedSendSize = cp._expectedSendSize;
	_sentSize = cp._sentSize;
	_should_close = cp._should_close;
	_one_shot = cp._one_shot;
	_header_error = cp._header_error;
	_socket_error = cp._socket_error;
	_completed_content = cp._completed_content;
	_kernel_available = cp._kernel_available;
	_bind = cp._bind;
	return (*this);
}
FileDescriptorAttributes::~FileDescriptorAttributes() {}

DefaultType<long>		&FileDescriptorAttributes::getExpectedRecvSize() { return (_expectedRecvSize); }
DefaultType<long>		&FileDescriptorAttributes::getReceivedSize() { return (_receivedSize); }
DefaultType<long>		&FileDescriptorAttributes::getExpectedSendSize() { return (_expectedSendSize); }
DefaultType<long>		&FileDescriptorAttributes::getSentSize() { return (_sentSize); }
Bind					*FileDescriptorAttributes::getBind() { return (_bind); }
DefaultType<Request>	&FileDescriptorAttributes::getHeader() { return (_header); }
DefaultType<bool>		&FileDescriptorAttributes::cgiReady() { return (_cgiReady); }
DefaultType<bool>		&FileDescriptorAttributes::cgiReady(bool val) { _cgiReady.setValue(val); return (_cgiReady); }




void		FileDescriptorAttributes::setExpectedRecvSize(long val) { _expectedRecvSize.setValue(val); }
void		FileDescriptorAttributes::setReceivedSize(long val) { _receivedSize.setValue(val); }
void		FileDescriptorAttributes::setExpectedSendSize(long val) { _expectedSendSize.setValue(val); }
void		FileDescriptorAttributes::setSentSize(long val) {_sentSize.setValue(val); }
void		FileDescriptorAttributes::setBind(Bind *bind) { _bind = bind; }
void		FileDescriptorAttributes::setContent(char *str) { _content = std::string(str); }
void		FileDescriptorAttributes::setContent(std::string str) { _content = (str); }
void		FileDescriptorAttributes::addContent(char *str) { _content += str; }
std::string	&FileDescriptorAttributes::getContent(void) { return (_content); }
void		FileDescriptorAttributes::setHeader(std::string &str)
{
	_header.setValue(Request(_bind));
	_header.Value().setHeader(str);
}

bool		FileDescriptorAttributes::timedOut(void) 
{
	struct timespec now;
	double elapsed;

	clock_gettime(CLOCK_MONOTONIC, &now);
	elapsed = (now.tv_sec - _createdTime.tv_sec) + ((now.tv_nsec - _createdTime.tv_nsec) / 1000000000.0);
	return (elapsed > static_cast<double>(DFL_TIMEOUT)); 
}

bool	FileDescriptorAttributes::shouldClose(void) { return (_should_close); }
bool	FileDescriptorAttributes::shouldClose(bool val) { _should_close = val; return (_should_close); }
bool	FileDescriptorAttributes::oneShot(void) { return (_one_shot); }
bool	FileDescriptorAttributes::oneShot(bool val) { _one_shot = val; return (_one_shot); }
size_t	FileDescriptorAttributes::headerError(void) { return (_header_error); }
size_t	FileDescriptorAttributes::headerError(size_t val) { _header_error = val; return (_header_error); }
bool	FileDescriptorAttributes::socketError(void) { return (_socket_error); }
bool	FileDescriptorAttributes::socketError(bool val) { _socket_error = val; return (_socket_error); }
bool	FileDescriptorAttributes::completedContent(void) { return (_completed_content); }
bool	FileDescriptorAttributes::completedContent(bool val) { _completed_content = val; return (_completed_content); }
ssize_t	FileDescriptorAttributes::kernelAvailable(void) { return (_kernel_available); }
ssize_t	FileDescriptorAttributes::kernelAvailable(ssize_t val) { _kernel_available = val; return (_kernel_available); }
int		FileDescriptorAttributes::getKind(void) { return (_kind); }
