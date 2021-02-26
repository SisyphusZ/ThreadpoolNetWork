 ///
 /// @file    TimerThread.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-04-01 16:16:36
 ///

#ifndef __TIMERTHREAD_H__
#define __TIMERTHREAD_H__

#include "Thread.h"
#include "Timer.h"

namespace sp
{

class TimerThread
{
public:
	TimerThread(int initTime,int interTime,TimerCallback cb);
	~TimerThread();
	void start();
	void stop();
private:
	Timer _timer;
	Thread _thread;
};

}//end of namespace sp

#endif
