 ///
 /// @file    Dictionary.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 20:57:46
 ///

#include "Dictionary.h"
#include <stdlib.h>
#include <functional>
#include <fstream>
#include <sstream>
using std::ifstream;
using std::istringstream;

namespace sp
{

void Dictionary::destroy()
{
	if(pDictionary)
	{
		delete pDictionary;
	}
}

void Dictionary::init()
{
	::atexit(destroy);
	pDictionary=new Dictionary();
}

Dictionary * Dictionary::createDicitionary()
{
	::pthread_once(&once,init);
	return pDictionary;
}

Dictionary::Dict & Dictionary::getDict()
{
	return _dict;
}

Dictionary::Index & Dictionary::getIndex()
{
	return _index;
}

void Dictionary::setDict(const string path)
{
	ifstream ifs(path);
	if(!ifs.good())
	{
		fprintf(stderr,"词典文件读取失败");
		exit(EXIT_FAILURE);
	}
	string line;
	string word;
	int freq;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		while(iss>>word&&iss>>freq)
		{
			_dict.push_back(std::make_pair(word,freq));
		}
	}
	ifs.close();
}

void Dictionary::setIndex(const string path)
{
	ifstream ifs(path);
	if(!ifs.good())
	{
		fprintf(stderr,"索引文件打开失败");
		exit(EXIT_FAILURE);
	}
	_index.reserve(26);
#if 0
	cout<<"before for"<<endl;
	cout<<"_index.szie()="<<_index.size()<<endl;
	for(auto it=_index.begin();it!=_index.end();++it)
	{
		for(auto iit=it->begin();iit!=it->end();++iit)
		{
			cout<<*iit<<' ';
		}
		cout<<endl;
	}
	cout<<"end of for"<<endl;
#endif
	string line;
	int index;
	int idx=0;
	while(idx<26)
	{
		while(getline(ifs,line))
		{
			set<int> tmp;
	//		cout<<"line="<<line<<endl;
			if(!line.empty())
			{
				istringstream iss(line);
				while(iss>>index)
				{
					tmp.insert(index);
				}
//				for(auto num : tmp)
//				{	cout<<num<<" ";	}
				_index.push_back(tmp);
//				cout<<endl;
			}else{
				set<int> nodata;
//				for(auto num : nodata)
//				{	cout<<num<<" ";	}
				_index.push_back(nodata);
	//			cout<<"index="<<' '<<endl;
			}
		}
		++idx;
	}
}


/*************debug*****************/

void Dictionary::showDict()
{
	for(auto & elem : _dict)
	{
		cout<<elem.first<<"\t"<<elem.second<<endl;
	}
}

void Dictionary::showIndex()
{
	for(auto & elem1 :_index)
	{
		for(auto elem2 : elem1)
		{
			cout<<elem2<<' ';
		}
		cout<<endl;
	}
}

Dictionary * Dictionary::pDictionary=NULL;
pthread_once_t Dictionary::once=PTHREAD_ONCE_INIT;
}//end of namespace sp
