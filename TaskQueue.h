 ///
 /// @file    TaskQueue.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 22:39:58
 ///

#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>
using std::queue;

namespace sp
{

class TaskQueue
{
public:
	typedef std::function<void()> Task;
	TaskQueue(size_t queSize);

	bool full();
	bool empty();

	void push(Task task);
	Task pop();

	void wakeup();
private:
	size_t _queSize;
	queue<Task> _que;
	MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
	bool _flag;
};

}//end of namespace sp

#endif
