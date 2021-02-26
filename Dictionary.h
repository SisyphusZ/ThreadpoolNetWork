 ///
 /// @file    Dictionary.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 20:48:17
 ///

#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <vector>
#include <utility>
#include <set>
#include <string>
#include <iostream>
#include <pthread.h>
using std::vector;
using std::set;
using std::pair;
using std::string;
using std::endl;
using std::cout;

namespace sp
{

class Dictionary
{
public:
	typedef vector<pair<string,int> > Dict;
	typedef vector<set<int> > Index;
	
	static Dictionary * createDicitionary();
	static void init();
	static void destroy();
	void setDict(const string filename);
	void setIndex(const string filename);
	Dict & getDict();
	Index & getIndex();
	void showDict();//debug
	void showIndex();//debug
private:
	static Dictionary * pDictionary;
	static pthread_once_t once;
	Dictionary(){};
	~Dictionary(){};
	Dict _dict;
	Index _index;
};

}//end of namespace sp

#endif
