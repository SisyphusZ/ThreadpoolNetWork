 ///
 /// @file    Timer.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-04-01 15:25:37
 ///

#ifndef __TIMER_H__
#define __TIMER_H__

#include <sys/timerfd.h>
#include <functional>

namespace sp
{

typedef std::function<void()> TimerCallback;

class Timer
{
public:
	Timer(int initTime,int interTime,TimerCallback cb);
	void start();
	void stop();
private:
	void handleRead();
private:
	int _fd;
	int _initTime;
	int _interTime;
	TimerCallback _cb;
	bool _isStart;
};

}//end of namespace sp


#endif
