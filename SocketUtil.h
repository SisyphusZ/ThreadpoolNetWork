 ///
 /// @file    SocketUtil.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 09:41:59
 ///

#ifndef __SOCKETUTIL_H__
#define __SOCKETUTIL_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/eventfd.h>
#include <sys/epoll.h>
#include <iostream>
namespace sp
{

inline
int createSocketFd()
{
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==fd)
	{
		perror("create socketfd error");
	}
	return fd;
}

inline 
void setNonblock(int fd)
{
	int flag=::fcntl(fd,F_GETFL,0);
	flag|=O_NONBLOCK;
	::fcntl(fd,F_SETFL,flag);
}

inline
int createEpollFd()
{
	int fd=::epoll_create1(0);
	if(fd==-1)
	{
		perror("epoll create error");
		exit(EXIT_FAILURE);
	}
	return fd;
}

inline
void addEpollFd(int efd,int fd)
{
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN;
	if(-1==::epoll_ctl(efd,EPOLL_CTL_ADD,fd,&ev))
	{
		perror("add epoll fd error");
		exit(EXIT_FAILURE);
	}
}

inline 
void delEpollFd(int efd,int fd)
{
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN;
	if(-1==::epoll_ctl(efd,EPOLL_CTL_DEL,fd,&ev))
	{
		perror("del epoll fd error");
		exit(EXIT_FAILURE);
	}
}

inline
int createEventFd()
{
	int evtfd=::eventfd(0,EFD_NONBLOCK|EFD_CLOEXEC);
	if(-1==evtfd)
	{
		perror("eventfd create error");
		exit(EXIT_FAILURE);
	}
	return evtfd;
}

inline
size_t recvPeek(int sockfd,void * buf,size_t len)
{
	int ret;
	do
	{
		ret=recv(sockfd,buf,len,MSG_PEEK);
	}while(ret==-1&&errno==EINTR);
	return ret;
}

inline
bool isConnectionClosed(int sockfd)
{
	char buf[1024]={0};
	int nread=recvPeek(sockfd,buf,sizeof(buf));
	if(-1==nread)
	{
		perror("recv error");
		exit(EXIT_FAILURE);
	}
	return (nread==0);
}
}//end of namespace sp

#endif
