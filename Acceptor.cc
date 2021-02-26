 ///
 /// @file    Acceptor.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 10:01:50
 ///

#include "Acceptor.h"
#include "SocketUtil.h"

namespace sp
{

Acceptor::Acceptor(int fd,const InetAddress & addr)
:listenSock_(fd)
,addr_(addr)
{}

void Acceptor::ready()
{
	setReuseAddr(true);
	setReusePort(true);
	bind();
	listen();
}

void Acceptor::setReusePort(bool no)
{
	int flag=(no?1:0);
	if(::setsockopt(listenSock_.fd(),
					SOL_SOCKET,
					SO_REUSEPORT,
					&flag,
					static_cast<socklen_t>(sizeof(flag)))==-1)
	{
		perror("set reuse port error");
		::close(listenSock_.fd());
		exit(EXIT_FAILURE);
	}
}

void Acceptor::setReuseAddr(bool no)
{
	int flag=(no?1:0);
	if(::setsockopt(listenSock_.fd(),
					SOL_SOCKET,
					SO_REUSEADDR,
					&flag,
					static_cast<socklen_t>(sizeof(flag)))==-1)
	{
		perror("set reuse addr error");
		::close(listenSock_.fd());
		exit(EXIT_FAILURE);
	}
}

void Acceptor::bind()
{
	if(::bind(listenSock_.fd(),(struct sockaddr*)addr_.get(),sizeof(addr_))==-1)
	{
		perror("bind error");
		::close(listenSock_.fd());
		exit(EXIT_FAILURE);
	}
}

void Acceptor::listen()
{
	if(::listen(listenSock_.fd(),10)==-1)
	{
		perror("listen error");
		::close(listenSock_.fd());
		exit(EXIT_FAILURE);
	}
}

int Acceptor::accept()
{
	int fd=::accept(listenSock_.fd(),NULL,NULL);
	if(fd==-1)
	{
		perror("accept error");
		exit(EXIT_FAILURE);
	}
	return fd;
}
}//end of namespace sp
