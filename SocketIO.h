 ///
 /// @file    SocketIO.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 10:14:02
 ///

#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

#include <stdio.h>


namespace sp
{

class SocketIO
{
public:
	SocketIO(int fd);
	size_t readn(char * buf,size_t count);
	size_t writen(const char * buf,size_t count);
	size_t readline(char * buf,size_t maxlen);
private:
	size_t recv_peek(char * buf,size_t count);
private:
	int fd_;
};

}//end of namespace sp

#endif
