 ///
 /// @file    TcpConnection.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 15:01:20
 ///

#include "TcpConnection.h"
#include "EpollPoller.h"
#include <string.h>
#include <stdio.h>

namespace sp
{

TcpConnection::TcpConnection(int sockfd,EpollPoller * loop)
:sockfd_(sockfd)
,sockIO_(sockfd_.fd())
,localAddr_(Socket::getLocalAddr(sockfd_.fd()))
,peerAddr_(Socket::getPeerAddr(sockfd_.fd()))
,isShutdownWrite_(false)
,loop_(loop)
{}

TcpConnection::~TcpConnection()
{
	if(!isShutdownWrite_)
	{
		shutdown();
	}
}

std::string TcpConnection::receive()
{
	char buf[65536]={0};
	size_t ret=sockIO_.readline(buf,sizeof(buf));
	if(ret==0)
	{
		return std::string();
	}else{
		return std::string(buf);
	}
}

void TcpConnection::send(const std::string & msg)
{
	sockIO_.writen(msg.c_str(),msg.size());
}

void TcpConnection::sendInLoop(const std::string & msg)
{
	if(loop_)
	{
		loop_->runInLoop(std::bind(&TcpConnection::send,this,msg));
	}
}

void TcpConnection::shutdown()
{
	if(!isShutdownWrite_)
	{
		sockfd_.shutdownWrite();
		isShutdownWrite_=true;
	}	
}

std::string TcpConnection::toString()
{
	char buf[100]={0};
	snprintf(buf,sizeof(buf),"%s:%d->%s:%d",localAddr_.ip().c_str(),
											localAddr_.port(),
											localAddr_.ip().c_str(),
											localAddr_.port());
	return std::string(buf);
}

void TcpConnection::setConnectionCallback(TcpConnectionCallback cb)
{
	onConnectionCb_=cb;
}

void TcpConnection::setMessageCallback(TcpConnectionCallback cb)
{
	onMessageCb_=cb;
}

void TcpConnection::setCloseCallback(TcpConnectionCallback cb)
{
	onCloseCb_=cb;
}

void TcpConnection::handleConnctionCallback()
{
	if(onConnectionCb_)
	{
		onConnectionCb_(shared_from_this());
	}
}

void TcpConnection::handleMessageCallback()
{
	if(onMessageCb_)
	{
		onMessageCb_(shared_from_this());
	}
}

void TcpConnection::handleCloseCallback()
{
	if(onCloseCb_)
	{
		onCloseCb_(shared_from_this());
	}
}
}//end of namespace sp
