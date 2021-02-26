 ///
 /// @file    TaskQueue.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 22:45:24
 ///

#include "TaskQueue.h"
#include <iostream>
#include <pthread.h>
using std::cout;
using std::endl;
namespace sp
{

TaskQueue::TaskQueue(size_t queSize)
:_queSize(queSize)
,_mutex()
,_notFull(_mutex)
,_notEmpty(_mutex)
,_flag(true)
{}

bool TaskQueue::full()
{
	return _que.size()==_queSize;
}

bool TaskQueue::empty()
{
	return _que.empty();
}

void TaskQueue::push(Task task)
{
	MutexLockGuard mlg(_mutex);
	while(full())
	{
		_notFull.wait();
	}
	_que.push(task);
	_notEmpty.notify();
}

TaskQueue::Task TaskQueue::pop()
{
	MutexLockGuard mlg(_mutex);
	while(_flag&&empty())
	{
		_notEmpty.wait();
	}
	if(_flag)
	{
		Task task=_que.front();
		_que.pop();
		_notFull.notify();
		cout<<"线程获取任务成功"<<endl;
		return task;
	}else{
		return NULL;
	}
}

void TaskQueue::wakeup()
{
	_flag=false;
	_notEmpty.notify_all();
}

}//end of namespace sp
