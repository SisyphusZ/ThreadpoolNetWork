 ///
 /// @file    MutexLock.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 22:00:59
 ///

#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include "Noncopyable.h"
#include <pthread.h>

namespace sp
{

class MutexLock
:Noncopyable
{
public:
	MutexLock();
	~MutexLock();

	void lock();
	void unlock();
	pthread_mutex_t * get();
	bool isLocking();
private:
	pthread_mutex_t _mutex;
	bool _isLocking;
};

class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock & mutex);
	~MutexLockGuard();
private:
	MutexLock & _mutex;
};

}//end of namespace sp

#endif
