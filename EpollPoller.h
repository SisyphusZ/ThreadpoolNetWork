 ///
 /// @file    EpollPoller.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 10:55:05
 ///

#ifndef __EPOLLPOLLER_H__
#define __EPOLLPOLLER_H__

#include "TcpConnection.h"
#include "MutexLock.h"

#include <sys/epoll.h>
#include <vector>
#include <map>
#include <functional>
namespace sp
{

class Acceptor;

class EpollPoller
{
public:
	typedef TcpConnection::TcpConnectionCallback EpollCallback;
	typedef std::function<void()> Functor;

	EpollPoller(Acceptor & acceptor);
	~EpollPoller();

	void loop();
	void unloop();
	void runInLoop(const Functor && cb);
	void doPendingFunctors();
	void wakeup();

	void setConnectionCallback(EpollCallback cb);
	void setMessageCallback(EpollCallback cb);
	void setCloseCallback(EpollCallback cb);
private:
	void waitEpollFd();
	void handleConnection();
	void handleMessage(int peerfd);
	void handleRead();
private:
	Acceptor & acceptor_;
	int epollfd_;
	int eventfd_;
	int listenfd_;
	bool isLooping_;

	MutexLock mutex_;
	std::vector<Functor> _pendingFunctors;

	typedef std::vector<struct epoll_event> EventList;
	EventList eventsList_;

	typedef std::map<int,TcpConnectionPtr> ConnectionMap;
	ConnectionMap connMap_;
	
	EpollCallback onConnectionCb_;
	EpollCallback onMessageCb_;
	EpollCallback onCloseCb_;

};

}//end of namespace sp

#endif
