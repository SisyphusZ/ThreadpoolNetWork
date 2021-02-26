 ///
 /// @file    Socket.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 09:49:41
 ///

#include "Socket.h"
#include "SocketUtil.h"
#include "InetAddress.h"

namespace sp
{

Socket::Socket()
:fd_(createSocketFd())
{}

Socket::Socket(int fd)
:fd_(fd)
{}

Socket::~Socket()
{
	::close(fd_);
}

void Socket::shutdownWrite()
{
	if(::shutdown(fd_,SHUT_WR)==-1)
	{
		perror("shutdown write error");
	}
}

void Socket::nonblock()
{
	setNonblock(fd_);
}

InetAddress Socket::getPeerAddr(int sockfd)
{
	struct sockaddr_in addr;
	::memset(&addr,0,sizeof(addr));
	socklen_t len=sizeof(addr);
	if(::getpeername(sockfd,(struct sockaddr*)(&addr),&len)==-1)
	{
		perror("get peer addr error");
	}
	return InetAddress(addr);
}

InetAddress Socket::getLocalAddr(int sockfd)
{
	struct sockaddr_in addr;
	::memset(&addr,0,sizeof(addr));
	socklen_t len=sizeof(addr);
	if(::getsockname(sockfd,(struct sockaddr*)(&addr),&len)==-1)
	{
		perror("get local addr error");
	}
	return InetAddress(addr);
}
}//end of namespace sp
