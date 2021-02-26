 ///
 /// @file    TimerThread.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-04-01 16:25:03
 ///

#include "TimerThread.h"
#include <iostream>
using std::cout;
using std::endl;


namespace sp
{

TimerThread::TimerThread(int initTime,int interTime,TimerCallback cb)
:_timer(initTime,interTime,cb)
,_thread(std::bind(&Timer::start,&_timer),"-1")
{
	cout<<"定时器线程创建完毕"<<endl;
}

void TimerThread::start()
{
	_thread.start();
	cout<<"定时器线程启动完毕"<<endl;
}

void TimerThread::stop()
{
	_thread.join();
}

TimerThread::~TimerThread()
{
	stop();
}
}//end of namespace sp
