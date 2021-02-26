 ///
 /// @file    Thread.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 23:02:00
 ///

#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>
#include <string>
using std::string;


namespace sp
{

namespace current_thread
{
	extern __thread const char * threanName;
}

class Thread
{
public:
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback cb,string name);
	~Thread();
	void start();
	void join();
private:
	static void * threadFunc(void * p);
private:
	pthread_t _pthId;
	bool _isRunning;
	ThreadCallback _cb;
	string _name;
};

}//end of namespace of sp

#endif
