 ///
 /// @file    TcpServer.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 16:19:15
 ///

#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "Acceptor.h"
#include "EpollPoller.h"

namespace sp
{

class TcpServer
{
public:
	typedef EpollPoller::EpollCallback TcpServerCallback;
	TcpServer(const std::string ip,unsigned short port);

	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback cb);
	void setMessageCallback(TcpServerCallback cb);
	void setCloseCallback(TcpServerCallback cb);
private:
	Acceptor acceptor_;
	EpollPoller poller_;

	TcpServerCallback onConnectionCb_;
	TcpServerCallback onMessageCb_;
	TcpServerCallback onCloseCb_;
};

}//end of namespace sp

#endif
