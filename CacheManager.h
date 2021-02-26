 ///
 /// @file    CacheManager.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-30 11:29:40
 ///

#ifndef __CACHEMANAGER_H__
#define __CACHEMANAGER_H__

#include "Cache.h"
#include <vector>
using std::vector;

namespace sp
{

class CacheManager
{
public:
	static void initCache(size_t size,const string & filename);
	static Cache & getCache(size_t idx);
	static void periodicUpdateCaches();
private:
	static vector<Cache> _cacheList;
};

}//end of namespac

#endif
