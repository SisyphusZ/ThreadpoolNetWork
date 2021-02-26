 ///
 /// @file    CacheManager.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-30 11:33:53
 ///

#include "CacheManager.h"
#include <iostream>
#include <fstream>
using std::ofstream;
using std::cout;
using std::endl;

namespace sp
{

vector<Cache> CacheManager::_cacheList;

void CacheManager::initCache(size_t size,const string & filename)
{
	CacheManager::_cacheList.reserve(size);
	for(size_t idx=0;idx!=size;++idx)
	{
		_cacheList.push_back(Cache());
	}
	for(auto & elem : _cacheList)
	{
		elem.readFromFile(filename);
	}
}

Cache & CacheManager::getCache(size_t idx)
{
	if(idx>=CacheManager::_cacheList.size())
	{
		_cacheList.resize(CacheManager::_cacheList.size()*2);
	}
	return _cacheList[idx];
}

void CacheManager::periodicUpdateCaches()
{
	/*同步每一个cache*/
	auto first=_cacheList.begin();
	auto it=_cacheList.begin();
	++it;
	//1.将每一个cache中的内容都写入cache1中
	for(;it!=_cacheList.end();++it)
	{
		std::unordered_map<string,string> hashMap=it->get();
		for(auto & elem : hashMap)
		{
			first->push(elem.first,elem.second);	
		}
	}
	//2.将cache1中的内容都写入每一个cache中
	it=_cacheList.begin();
	++it;
	std::unordered_map<string,string> cache1=first->get();
	for(;it!=_cacheList.end();++it)
	{
		for(auto & elem :cache1)
		{
			it->push(elem.first,elem.second);
		}
	}
#if 0
	for(auto & elem : cache1)
	{
		for(;it!=_cacheList.end();++it)
		{
			it->push(elem.first,elem.second);
		}
	}
#endif
	cout<<"同步cache完成"<<endl;
	/*debug*/
	int idx=0;
	for(auto it=_cacheList.begin();it!=_cacheList.end();++it)
	{
		std::unordered_map<string,string> temp=it->get();
	cout<<"************" << ++idx <<" ***************"<<endl;
		for(auto & elem : temp)
		{
			cout<<elem.first<<"\t"<<elem.second<<endl;
		}
	cout<<"**********************************"<<endl;
	}
	/*将cache写入文件中*/
	ofstream ofs("cache");
	std::unordered_map<string,string> hashMap=first->get();
	for(auto it=hashMap.begin();it!=hashMap.end();++it)
	{
		ofs<<it->first;
		ofs<<' ';
		ofs<<it->second;
		ofs<<endl;
	}
}

}//end of namespace sp
