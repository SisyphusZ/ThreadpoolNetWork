 ///
 /// @file    TcpServer.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 16:37:10
 ///

#include "TcpServer.h"
#include "InetAddress.h"
#include "SocketUtil.h"
#include <iostream>
using std::cout;
using std::endl;

namespace sp
{

TcpServer::TcpServer(const std::string ip,unsigned short port)
:acceptor_(createSocketFd(),InetAddress(ip.c_str(),port))
,poller_(acceptor_)
{}

void TcpServer::start()
{
	acceptor_.ready();
	poller_.setConnectionCallback(onConnectionCb_);
	poller_.setMessageCallback(onMessageCb_);
	poller_.setCloseCallback(onCloseCb_);
	poller_.loop();
}

void TcpServer::stop()
{
	poller_.unloop();
}


void TcpServer::setConnectionCallback(TcpServerCallback cb)
{
	onConnectionCb_=cb;
}

void TcpServer::setMessageCallback(TcpServerCallback cb)
{
	onMessageCb_=cb;
}

void TcpServer::setCloseCallback(TcpServerCallback cb)
{
	onCloseCb_=cb;
}
}//end of namespace sp
