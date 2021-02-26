 ///
 /// @file    Condition.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 22:32:21
 ///

#include "Condition.h"
#include "MutexLock.h"

namespace sp
{

Condition::Condition(MutexLock & mutex)
:_mutex(mutex)
{
	pthread_cond_init(&_cond,NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&_cond);
}

void Condition::wait()
{
	pthread_cond_wait(&_cond,_mutex.get());
}

void Condition::notify()
{
	pthread_cond_signal(&_cond);
}

void Condition::notify_all()
{
	pthread_cond_broadcast(&_cond);
}

}//end of namespace sp
