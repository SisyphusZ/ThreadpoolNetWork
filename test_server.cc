 ///
 /// @file    test_server.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-28 17:01:12
 ///

#include "QueryServer.h"
#include <iostream>
#include <unistd.h>

int main(void)
{
	sp::QueryServer server(10,4,60,30,"127.0.0.1",8888,"dict","index");
	server.start();
}
