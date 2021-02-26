 ///
 /// @file    TcpConnection.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 10:45:48
 ///

#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"

#include <string>
#include <memory>
#include <functional>
#include <vector>

namespace sp
{

class EpollPoller;
class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection
:public std::enable_shared_from_this<TcpConnection>
{
public:
	typedef std::function<void(TcpConnectionPtr) > TcpConnectionCallback;
	TcpConnection(int fd,EpollPoller * loop);
	~TcpConnection();

	std::string receive();
	void send(const std::string & msg);
	void sendInLoop(const std::string & msg);
	void shutdown();

	std::string toString();

	void setConnectionCallback(TcpConnectionCallback cb);
	void setMessageCallback(TcpConnectionCallback cb);
	void setCloseCallback(TcpConnectionCallback cb);

	void handleConnctionCallback();
	void handleMessageCallback();
	void handleCloseCallback();
private:
	Socket sockfd_;
	SocketIO sockIO_;
	const InetAddress localAddr_;
	const InetAddress peerAddr_;
	bool isShutdownWrite_;
	EpollPoller * loop_;

	TcpConnectionCallback onConnectionCb_;
	TcpConnectionCallback onMessageCb_;
	TcpConnectionCallback onCloseCb_;
};

}//end of namespace sp

#endif
