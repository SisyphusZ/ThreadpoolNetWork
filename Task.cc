 ///
 /// @file    Task.cc
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-27 17:15:10
 ///

#include "Task.h"
#include "Dictionary.h"
#include "CacheManager.h"
#include "Thread.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sstream>
#define  min(a,b) ((a<b)?a:b)
namespace sp
{

inline
int str2int(string word)
{
	int num;
	std::istringstream iss(word);
	iss>>num;
	return num;
}

Task::Task(string word)
:_queryWord(word)
{}

#if 1
int Task::distance(const string candidate)
{
	//step 1
	int n = candidate.length();
	int m = _queryWord.length();
	if (m == 0) return n;
	if (n == 0) return m;
	//Construct a matrix
	typedef vector< vector<int> >  Tmatrix;
	Tmatrix matrix(n + 1);
	for (int i = 0; i <= n; i++)  matrix[i].resize(m + 1);
	//step 2 Initialize

	for (int i = 1; i <= n; i++) matrix[i][0] = i;
	for (int i = 1; i <= m; i++) matrix[0][i] = i;

	//step 3
	for (int i = 1; i <= n; i++)
	{
		const char si = candidate[i - 1];
		//step 4
		for (int j = 1; j <= m; j++)
		{

			const char dj = _queryWord[j - 1];
			//step 5
			int cost;
			if (si == dj){
				cost = 0;
			}
			else{
				cost = 2;
			}
			//step 6
			const int above = matrix[i - 1][j] + 1;
			const int left = matrix[i][j - 1] + 1;
			const int diag = matrix[i - 1][j - 1] + cost;
			matrix[i][j] = min(above, min(left, diag));
		}
	}//step7
	return matrix[n][m];
}
#endif

set<int> Task::query_Index(Dictionary * dict)
{
	set<int> ret;
	vector<set<int> > index=dict->getIndex(); 
	for(size_t idx=0;idx!=_queryWord.size()-1;++idx)//客户端传递过来的单词会末尾会多一个回车，因此要减1
	{
		int no=_queryWord[idx]-'a';
		for(auto & elem : index[no])
		{
			ret.insert(elem);
		}
	}
#if 0
	for(auto & elem : ret)
	{
		cout<<elem<<' ';
	}
	cout<<endl;
#endif
	return ret;
}

vector<pair<string,int> > Task::query_Dict(Dictionary * dict)
{
	set<int> index=query_Index(dict);
	vector<pair<string,int> > Dict=dict->getDict();
	vector<pair<string,int> > result;
	for(auto & elem : index)
	{
		result.push_back(Dict[elem]);
	}
#if 0
	for(auto & elem : result)
	{
		cout<<elem.first<<' '<<elem.second<<endl;
	}
#endif
	return result;
}

void Task::process(Dictionary * dict,TcpConnectionPtr conn)
{
	cout<<"--------------------------------------"<<endl;
	cout<<">线程"<<current_thread::threanName<<"执行查找操作"<<endl;
	Cache &  cache=CacheManager::getCache(str2int(current_thread::threanName));
	cout<<"1.获取线程cache成功"<<endl;
	char word[50]={0};
	::strncpy(word,_queryWord.c_str(),_queryWord.size()-1);//去掉末尾的换行符
	cout<<"2.前往cache查找数据"<<endl;
	string value=cache.search(word);
	if(value.empty())
	{
		cout<<"3.cache中无该数据"<<endl;
		Result result;
		cout<<"4.前往词典查找数据"<<endl;
		vector<pair<string,int> > candidate=query_Dict(dict);	
		if(candidate.empty())
		{
			cout<<"5.词典中查无结果，返回原单词:"<<_queryWord<<endl;
			conn->sendInLoop(_queryWord);
			return;
		}
		for(auto & elem : candidate)
		{
			result._word=elem.first;
			result._freq=elem.second;
			result._dist=distance(elem.first);
			if(result._dist<=5)
			{
				_result.push(result);
			}
		}
		cout<<"5.词典中获取数据成功"<<endl;
#if 1
		while(!_result.empty())
		{
			Result tmp=_result.top();
			_ret.push_back(tmp._word);
			_result.pop();
		}
		char buf[1000]={0};
#if 0
	for(auto & elem : _ret)
	{
		cout<<elem<<endl;
	}
#endif
#if 1
		auto it=_ret.begin();
		strcpy(buf,(*it).c_str());
		int cnt=4;
		for(it+=1;it!=_ret.end();++it)
		{
			--cnt;
			strcat(buf," ");
			strcat(buf,(*it).c_str());
			if(!cnt)
			{
				break;
			}
		}
		cache.push(word,std::string(buf));
		cache.show();
		cout<<"6.更新cache数据"<<endl;
		cout<<">"<<current_thread::threanName<<"的cache中的数据为:"<<endl;
		cache.show();
		cout<<"--------------------------------------"<<endl;
//	cout<<buf<<endl;
		conn->sendInLoop(buf);
	}else{
		cout<<"3.cache数据比对成功"<<endl;
		cache.show();
		conn->sendInLoop(value);
		cout<<"--------------------------------------"<<endl;
	}
#endif
#if 0
	for(auto & elem : _ret)
	{
		cout<<elem<<endl;
	}
#endif
#endif
#if 0
	cout<<"线程"<<pthread_self()<<"查找单词"<<_queryWord<<endl;
	cout<<"候选词列表"<<endl;
	while(!_result.empty())
	{
		Result tmp=_result.top();
		cout<<"word:"<<tmp._word<<'\t';
		cout<<"freq:"<<tmp._freq<<'\t';
		cout<<"dist:"<<tmp._dist<<'\t';
		_result.pop();
		cout<<endl;
		::sleep(1);
	}
#endif
}

#if 1
vector<string> Task::getReturn()
{
	return _ret;
}
#endif
}
