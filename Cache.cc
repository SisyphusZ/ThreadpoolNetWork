 ///
 /// @file    Cache.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-30 11:06:01
 ///

#include "Cache.h"
#include <fstream>
#include <sstream>
#include <iostream>
using std::ifstream;
using std::istringstream;
using std::ofstream;

namespace sp
{

Cache::Cache(size_t size)
:_hashMap(size)
{
}

Cache::Cache(const Cache & cache)
:_hashMap(cache._hashMap)
{}

void Cache::push(const string & key,const string & value)
{
	_hashMap.insert(std::make_pair(key,value));
}

unordered_map<string,string> & Cache::get()
{
	return _hashMap;
}

void Cache::show()
{
	for(auto & elem : _hashMap)
	{
		std::cout<<elem.first<<" : "<<elem.second<<std::endl;
	}
}

string Cache::search(string key)
{
	auto it=_hashMap.find(key);
	if(it!=_hashMap.end())
	{
		return it->second;
	}else{
		return string();
	}
}

void Cache::readFromFile(const string filename)
{
	ifstream ifs(filename);
	if(ifs.good())
	{
		string line;
		string key;
		string value;
		while(getline(ifs,line))
		{
			istringstream iss(line);
			while(iss>>key)
			{
				getline(iss,value);
				_hashMap.insert(std::make_pair(key,value));
			}
		}
	}
	ifs.close();
}

void Cache::writeToFile(const string filename)
{
	ofstream ofs(filename);
	if(!ofs.good())
	{
		fprintf(stderr,"写入磁盘Cache，磁盘Cache打失败");
	}
	for(auto & elem : _hashMap)
	{
		ofs<<elem.first;
		ofs<<' ';
		ofs<<elem.second;
	}
	ofs.close();
}
}//end of namespace sp
