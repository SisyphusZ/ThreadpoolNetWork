 ///
 /// @file    Thread.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 23:05:27
 ///

#include "Thread.h"
#include <iostream>


namespace sp
{

namespace current_thread
{
	__thread const char * threanName="wd";
}

Thread::Thread(ThreadCallback cb,string name)
:_pthId(0)
,_isRunning(false)
,_cb(cb)
,_name(name)
{}

Thread::~Thread()
{
	if(_isRunning)
	{
		pthread_detach(_pthId);
	}
}

void Thread::start()
{
	pthread_create(&_pthId,NULL,threadFunc,this);
	std::cout<<"线程"<<_pthId<<"创建成功"<<std::endl;
	_isRunning=true;
}

void Thread::join()
{
	if(_isRunning)
	{
		pthread_join(_pthId,NULL);
		std::cout<<"线程"<<_pthId<<"回收成功"<<std::endl;
	}
}

void * Thread::threadFunc(void * p)
{
	Thread * thread=static_cast<Thread *>(p);
	current_thread::threanName=thread->_name.empty()?"wd":thread->_name.c_str();
	if(thread)
	{
			thread->_cb();
	}
	return NULL;
}

}//end of namesapce sp
