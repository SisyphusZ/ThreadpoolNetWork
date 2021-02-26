 ///
 /// @file    SocketIO.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 10:16:57
 ///

#include "SocketIO.h"
#include "SocketUtil.h"

namespace sp
{

SocketIO::SocketIO(int fd)
:fd_(fd)
{}

size_t SocketIO::readn(char * buf,size_t count)
{
	size_t nleft=count;
	char * pbuf=buf;
	while(nleft>0)
	{
		int nread=read(fd_,pbuf,nleft);
		if(nread==-1&&errno==EINTR)
		{
			continue;
		}else if(nread==-1){
			perror("read error");
			exit(EXIT_FAILURE);
		}else if(nread==0){
			break;
		}
		pbuf+=nread;
		nleft-=nread;
	}
	return (count-nleft);
}

size_t SocketIO::writen(const char * buf,size_t count)
{
	size_t nleft=count;
	const  char * pbuf=buf;
	while(nleft>0)
	{
		int nwrite=write(fd_,pbuf,nleft);
		if(nwrite==-1&&errno==EINTR)
		{
			continue;
		}else if(nwrite==-1){
			perror("write error");
			exit(EXIT_FAILURE);
		}
		pbuf+=nwrite;
		nleft-=nwrite;
	}
	return (count-nleft);
}

size_t SocketIO::recv_peek(char * buf,size_t count)
{
	int nrecv;
	do
	{
		nrecv=::recv(fd_,buf,count,MSG_PEEK);
	}while(nrecv==-1&&errno==EINTR);
	return nrecv;
}

size_t SocketIO::readline(char *buf,size_t maxlen)
{
	size_t nleft=maxlen-1;
	char * pbuf=buf;
	int total=0;
	while(nleft>0)
	{
		size_t nrecv=recv_peek(pbuf,nleft);
		if(nrecv<=0)
		{
			return nrecv;
		}
		for(size_t idx=0;idx!=nleft;++idx)
		{
			if(pbuf[idx]=='\n')
			{
				size_t nsize=idx+1;
				if(readn(pbuf,nsize)!=nsize)
				{
					exit(EXIT_FAILURE);
				}
				pbuf+=nsize;
				nleft-=nsize;
				total+=nsize;
				*pbuf=0;
				return total;
			}
		}
		if(readn(pbuf,nrecv)!=nrecv)
		{
			exit(EXIT_FAILURE);
		}
		pbuf+=nrecv;
		nleft-=nrecv;
		total+=nrecv;
	}
	*pbuf=0;
	return maxlen-1;
}
}//end of namespace sp
