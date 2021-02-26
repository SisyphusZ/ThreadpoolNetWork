 ///
 /// @file    Socket.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 09:46:20
 ///

#ifndef __SOCKET_H__
#define __SOCKET_H__

namespace sp
{

class InetAddress;

class Socket
{
public:
	Socket();
	Socket(int fd);
	~Socket();

	void shutdownWrite();
	void nonblock();

	int fd()const{	return fd_;	}
	static InetAddress getPeerAddr(int sockfd);
	static InetAddress getLocalAddr(int sockfd);
private:
	int fd_;
};

}//end of namespace sp

#endif
