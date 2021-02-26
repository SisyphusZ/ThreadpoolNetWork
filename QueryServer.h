 ///
 /// @file    QueryServer.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 16:44:05
 ///

#ifndef __QUERYSERVER_H__
#define __QUERYSERVER_H__

#include "Threadpool.h"
#include "TcpServer.h"
#include "Dictionary.h"
#include "CacheManager.h"
#include <stdio.h>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

namespace sp
{

class QueryServer
{
public:
	QueryServer(size_t queSize,size_t threadNum,int initTime,int interTime,const std::string & ip,unsigned short port,const string dict,const string index);
	void onConnnection(const sp::TcpConnectionPtr & conn);
	void onMessage(const sp::TcpConnectionPtr & conn);
	void onClose(const sp::TcpConnectionPtr & conn);
	void start();
private:
	Threadpool threadpool_;
	TcpServer server_;
	Dictionary * pDicitionary_;
	CacheManager cacheManager_;
};

}//end of namespace sp
#endif
