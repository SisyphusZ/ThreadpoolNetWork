 ///
 /// @file    Cache.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-30 10:58:14
 ///

#ifndef __CACHE_H__
#define __CACHE_H__

#include <string>
#include <unordered_map>
using std::unordered_map;
using std::string;

namespace sp
{

class Cache
{
public:
	Cache(size_t size=0);
	Cache(const Cache & cache);
	string search(string key);
	void push(const string & key,const string & value);
	void readFromFile(const string filename);
	void writeToFile(const string filename);
	unordered_map<string,string> & get();
	void show();//debug
private:
	unordered_map<string,string> _hashMap;
};

}//end of namespace sp

#endif
