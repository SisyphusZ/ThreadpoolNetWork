 ///
 /// @file    MutexLock.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 22:15:09
 ///

#include "MutexLock.h"

namespace sp
{

MutexLock::MutexLock()
{
	pthread_mutex_init(&_mutex,NULL);
	_isLocking=false;
}

MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&_mutex);
	_isLocking=false;
}

void MutexLock::lock()
{
	pthread_mutex_lock(&_mutex);
	_isLocking=true;
}

void MutexLock::unlock()
{
	pthread_mutex_unlock(&_mutex);
	_isLocking=false;
}

pthread_mutex_t * MutexLock::get()
{
	return & _mutex;
}

bool MutexLock::isLocking()
{
	return _isLocking;
}

MutexLockGuard::MutexLockGuard(MutexLock & mutex)
:_mutex(mutex)
{
	_mutex.lock();
}

MutexLockGuard::~MutexLockGuard()
{
	_mutex.unlock();
}
}//end of namespace sp
