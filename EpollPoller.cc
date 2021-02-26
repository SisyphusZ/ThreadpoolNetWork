 ///
 /// @file    EpollPoller.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 15:19:52
 ///

#include "EpollPoller.h"
#include "SocketUtil.h"
#include "Acceptor.h"
#include <assert.h>
#include <iostream>
using std::cout;
using std::endl;

namespace sp
{

EpollPoller::EpollPoller(Acceptor & acceptor)
:acceptor_(acceptor)
,epollfd_(createEpollFd())
,eventfd_(createEventFd())
,listenfd_(acceptor_.fd())
,isLooping_(false)
,mutex_()
,eventsList_(1024)
{
	addEpollFd(epollfd_,listenfd_);
	addEpollFd(epollfd_,eventfd_);
}

EpollPoller::~EpollPoller()
{
	::close(epollfd_);
}

void EpollPoller::loop()
{
	if(!isLooping_)
	{
		isLooping_=true;
		while(isLooping_)
		{
			waitEpollFd();			
		}
	}
}

void EpollPoller::unloop()
{
	if(isLooping_)
	{
		isLooping_=false;
	}
}

void EpollPoller::runInLoop(const Functor && cb)
{
	{
		MutexLockGuard mlg(mutex_);
		_pendingFunctors.push_back(std::move(cb));
	}
	wakeup();
}

void EpollPoller::doPendingFunctors()
{
	std::vector<Functor> tmp;
	{
		MutexLockGuard mlg(mutex_);
		tmp.swap(_pendingFunctors);
	}
	for(auto & functor : tmp)
	{
		functor();
	}
}

void EpollPoller::wakeup()
{
	uint64_t num=1;
	int ret=::write(eventfd_,&num,sizeof(num));
	if(ret!=sizeof(num))
	{
		perror("wakeup:write error");
		exit(EXIT_FAILURE);
	}
}

void EpollPoller::setConnectionCallback(EpollCallback cb)
{
	onConnectionCb_=cb;
}

void EpollPoller::setMessageCallback(EpollCallback cb)
{
	onMessageCb_=cb;
}

void EpollPoller::setCloseCallback(EpollCallback cb)
{
	onCloseCb_=cb;
}

void EpollPoller::waitEpollFd()
{
	int nready;
	do
	{
		nready=::epoll_wait(epollfd_,
							&(*eventsList_.begin()),
							eventsList_.size(),
							5000);
	}while(nready==-1&&errno==EINTR);
	if(nready==-1)
	{
		perror("epoll_wait errpr");
		exit(EXIT_FAILURE);
	}else if(nready==0){
//		cout<<"epoll timeout"<<endl;
	}else{
		if(nready==static_cast<int>(eventsList_.size()))
		{
			eventsList_.resize(eventsList_.size()*2);
		}
		for(int idx=0;idx!=nready;++idx)
		{
			/*当有新的连接请求时*/
			if(eventsList_[idx].data.fd==listenfd_)
			{
				if(eventsList_[idx].events&EPOLLIN)
				{
					handleConnection();
				}
			}
			/*当eventfd就绪时*/
			else if(eventsList_[idx].data.fd==eventfd_)
			{
				if(eventsList_[idx].events&EPOLLIN)
				{
					handleRead();
					doPendingFunctors();
				}
			}
			/*当客户端向服务器端发送信息时*/
			else
			{
				if(eventsList_[idx].events&EPOLLIN)
				{
					handleMessage(eventsList_[idx].data.fd);
				}
			}
		}//end of for
	}//end of else
}

void EpollPoller::handleConnection()
{
	int fd=acceptor_.accept();
	addEpollFd(epollfd_,fd);
	TcpConnectionPtr conn(new TcpConnection(fd,this));
	conn->setConnectionCallback(onConnectionCb_);
	conn->setMessageCallback(onMessageCb_);
	conn->setCloseCallback(onCloseCb_);
	std::pair<ConnectionMap::iterator,bool> ret;
	ret=connMap_.insert(std::make_pair(fd,conn));
	assert(ret.second==true);

	conn->handleConnctionCallback();
}

void EpollPoller::handleMessage(int fd)
{
	bool isClose=isConnectionClosed(fd);
	ConnectionMap::iterator it=connMap_.find(fd);
	assert(it!=connMap_.end());

	if(isClose)
	{
		it->second->handleCloseCallback();
		delEpollFd(epollfd_,fd);
		connMap_.erase(it);
	}else{
		it->second->handleMessageCallback();
	}
}

void EpollPoller::handleRead()
{
	uint64_t num;
	if(::read(eventfd_,&num,sizeof(uint64_t))==-1)
	{
		perror("handle read error");
	}
}
}//end of namespace sp
