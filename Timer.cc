 ///
 /// @file    Timer.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-04-01 15:29:29
 ///

#include "Timer.h"
#include <errno.h>
#include <poll.h>
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;


namespace sp
{

inline
int createTimerFd()
{
	int fd=::timerfd_create(CLOCK_REALTIME,0);
	if(-1==fd)
	{
		perror("timerfd_create error");
		exit(EXIT_FAILURE);
	}
	return fd;
}

inline
void setTimerFd(int fd,int initTime,int interTime)
{
	struct itimerspec time;
	time.it_value.tv_sec=initTime;
	time.it_value.tv_nsec=0;
	time.it_interval.tv_sec=interTime;
	time.it_interval.tv_nsec=0;
	if(timerfd_settime(fd,0,&time,0)==-1)
	{
		perror("set timerfd error");
		exit(EXIT_FAILURE);
	}
}

Timer::Timer(int initTime,int interTime,TimerCallback cb)
:_fd(createTimerFd())
,_initTime(initTime)
,_interTime(interTime)
,_cb(cb)
,_isStart(false)
{}

void Timer::start()
{
	struct pollfd pfd;
	pfd.fd=_fd;
	pfd.events=POLLIN;
	setTimerFd(_fd,_initTime,_interTime);
	_isStart=true;
	while(_isStart)
	{
		int nready=::poll(&pfd,1,5000);
		if(nready==-1&&errno==EINTR)
		{
			continue;
		}else if(nready==-1){
			perror("poll error");
			exit(EXIT_FAILURE);
		}else if(nready==0){
//			cout<<"poll timeout"<<endl;
		}else{
			if(pfd.revents&POLLIN)
			{
				handleRead();
				if(_cb)
				{
					_cb();
				}
			}
		}
	}
}

void Timer::stop()
{
	if(_isStart)
	{
		_isStart=false;
		setTimerFd(_fd,0,0);
	}
}

void Timer::handleRead()
{
	uint64_t n;
	int nread;
	do
	{
		nread=read(_fd,&n,sizeof(uint64_t));
	}while(nread==-1&&errno==EINTR);
}

}//end of namespace sp
