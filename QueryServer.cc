 ///
 /// @file    QueryServer.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 16:49:51
 ///

#include "QueryServer.h"
#include "Task.h"
#include "TimerThread.h"
#include <string.h>
#include <functional>
#include <iostream>
using namespace std::placeholders;
using std::cout;
using std::endl;

namespace sp
{


QueryServer::QueryServer(size_t queSize,size_t threadNum,int initTime,int interTime,const std::string & ip,unsigned short port,const string dict,const string index)
:threadpool_(queSize,threadNum,initTime,interTime)
,server_(ip,port)
,pDicitionary_(sp::Dictionary::createDicitionary())
{
	pDicitionary_->setDict(dict);
	pDicitionary_->setIndex(index);
	CacheManager::initCache(threadNum,"cache");
}

void QueryServer::start()
{
	threadpool_.start();
	server_.setConnectionCallback(std::bind(&QueryServer::onConnnection,this,_1));
	server_.setMessageCallback(std::bind(&QueryServer::onMessage,this,_1));
	server_.setCloseCallback(std::bind(&QueryServer::onClose,this,_1));
	server_.start();
}


void QueryServer::onConnnection(const sp::TcpConnectionPtr & conn)
{
	cout<<conn->toString()<<"连接建立"<<endl;
	conn->send("welcome to Query sercer");
}

void QueryServer::onMessage(const sp::TcpConnectionPtr & conn)
{
	std::string s(conn->receive());
	Task task(s);
	threadpool_.addTask(std::bind(&Task::process,task,pDicitionary_,conn));

#if 0
	std::cout<<1<<std::endl;
	vector<string> Return=task.getReturn();
	std::cout<<2<<std::endl;
	std::cout<<"Return.empty="<<Return.empty()<<endl;
	for(auto & elem : Return)
	{
	std::cout<<3<<std::endl;
		cout<<elem<<endl;
	}
	char buf[1000]={0};
	auto it=Return.begin();
	::strcpy(buf,(*it).c_str());
	for(auto it=Return.begin()+1;it!=Return.end();++it)
	{
		::strcat(buf," ");
		::strcat(buf,(*it).c_str());
	}
	cout<<"buf="<<buf<<endl;
	conn->sendInLoop(buf);
#endif
}

void QueryServer::onClose(const sp::TcpConnectionPtr & conn)
{
	cout<<conn->toString()<<"连接断开"<<endl;
}
}//end of namespace sp
