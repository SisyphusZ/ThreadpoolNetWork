 ///
 /// @file    Acceptor.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 09:58:17
 ///

#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "Socket.h"
#include "InetAddress.h"

namespace sp
{

class Acceptor
{
public:
	Acceptor(int fd,const InetAddress & addr);

	void ready();
	int accept();

	int fd()const{	return listenSock_.fd();	}
private:
	void setReuseAddr(bool no);
	void setReusePort(bool no);
	void bind();
	void listen();
private:
	Socket listenSock_;
	InetAddress addr_;
};

}//end of namespace sp

#endif
