 ///
 /// @file    Task.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-27 10:11:40
 ///

#ifndef __TASK_H__
#define __TASK_H__

#include "TcpConnection.h"
#include <queue>
#include <vector>
#include <string>
#include <set>
#include <utility>

using std::priority_queue;
using std::string;
using std::vector;
using std::set;
using std::pair;

namespace sp
{

struct Result
{
	string _word;
	int _freq;
	int _dist;
};

struct Compare
{
	bool operator()(Result lhs,Result rhs)
	{
		if(lhs._dist>rhs._dist)
		{
			return true;
		}else if(lhs._dist == rhs._dist && lhs._freq < rhs._freq){
			return true;
		}else if(lhs._freq == rhs._freq && lhs._word > rhs._word)
		{
			return true;
		}
		return false;
	}
};

class Dictionary;

class Task
{
public:
	typedef priority_queue<Result,vector<Result>,Compare> Candidate;
	Task(string word);
	void process(Dictionary * dict,TcpConnectionPtr conn);
	set<int> query_Index(Dictionary * dict);
	vector<pair<string,int> > query_Dict(Dictionary * dict);
	int distance(const string candidate);
	vector<string> getReturn();
private:
	string _queryWord;
	Candidate _result;
	vector<string> _ret;
};


}//end of namspace sp

#endif
