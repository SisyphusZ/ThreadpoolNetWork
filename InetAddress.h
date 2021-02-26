 ///
 /// @file    InetAddress.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 09:30:44
 ///

#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include <netinet/in.h>
#include <string>

namespace sp
{

class InetAddress
{
public:
	InetAddress(unsigned short port);
	InetAddress(const char * pIp,unsigned short port);
	InetAddress(const struct sockaddr_in & addr);

	const struct sockaddr_in * get()const;
	std::string ip()const;
	unsigned short port()const;
private:
	struct sockaddr_in addr_;
};

}//end of namespace sp

#endif
