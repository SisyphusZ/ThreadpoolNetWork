 ///
 /// @file    Threadpool.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 23:15:39
 ///

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h"
#include "TimerThread.h"
#include <functional>
#include <vector>
#include <memory>
using std::vector;
using std::shared_ptr;

namespace sp
{
class Thread;

class Threadpool
{
public:
	typedef std::function<void()> Task;
	Threadpool(size_t queSize,size_t threadNum,int initTime,int interTime);
	~Threadpool();

	void start();
	void stop();
	void addTask(Task task);
private:
	Task getTask();
	void threadFunc();
private:
	size_t _queSize;
	TaskQueue _que;
	size_t _threadNum;
	vector<shared_ptr<Thread> > _thread;
	int _initTime;
	int _interTime;
	shared_ptr<TimerThread> _timerThread;
	bool _isExit;
};

}//end of namespace sp

#endif
