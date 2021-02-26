 ///
 /// @file    Threadpool.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 23:22:06
 ///

#include "Threadpool.h"
#include "Thread.h"
#include "CacheManager.h"
#include "Timer.h"
#include <unistd.h>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::ostringstream;

inline
string int2str(int number)
{
	ostringstream oss;
	oss<<number;
	return oss.str();
}
namespace sp
{

Threadpool::Threadpool(size_t queSize,size_t threadNum,int initTime,int interTime)
:_queSize(queSize)
,_que(_queSize)
,_threadNum(threadNum)
,_initTime(initTime)
,_interTime(interTime)
,_isExit(false)
{
	_thread.reserve(_threadNum);
}


Threadpool::~Threadpool()
{
	if(!_isExit)
	{
		stop();
	}
}

void Threadpool::start()
{
	for(size_t idx=0;idx!=_threadNum;++idx)
	{
		shared_ptr<Thread> thread(new Thread(std::bind(&Threadpool::threadFunc,this),int2str(idx)));
		_thread.push_back(std::move(thread));
	}
	_timerThread.reset(new TimerThread(_initTime,_interTime,&CacheManager::periodicUpdateCaches));
	for(auto & thread : _thread)
	{
		thread->start();
	}
	_timerThread->start();
}

void Threadpool::stop()
{
	if(!_isExit)
	{
		while(!_que.empty())
		{
			::usleep(50);
		}
		_isExit=true;
		_que.wakeup();
		for(auto & thread : _thread)
		{
			thread->join();
		}
		_timerThread->stop();
	}
}

void Threadpool::addTask(Task task)
{
	_que.push(task);
}

Threadpool::Task Threadpool::getTask()
{
	return _que.pop();
}

void Threadpool::threadFunc()
{
	while(!_isExit)
	{
		std::cout<<"线程获取任务"<<std::endl;
		Task task=getTask();
		if(task)
		{
			cout<<"线程执行任务"<<endl;
			task();
		}
	}
}
}//end of namespace sp; 
