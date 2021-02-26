 ///
 /// @file    Condition.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 22:26:21
 ///

#ifndef __CONDITION_H__
#define __CONDITION_H__

#include <pthread.h>

namespace sp
{

class MutexLock;

class Condition
{
public:
	Condition(MutexLock & mutex);
	~Condition();

	void wait();
	void notify();
	void notify_all();
private:
	pthread_cond_t _cond;
	MutexLock & _mutex;
};

}//end of namespace sp

#endif
