 ///
 /// @file    Noncopyable.h
 /// @author  Sisyphus(2843658989@QQ.com)
 /// @date    2018-03-26 22:01:18
 ///

#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

namespace sp
{

class Noncopyable
{
public:
	Noncopyable(){};
	~Noncopyable(){};
private:
	Noncopyable(const Noncopyable &){};
	Noncopyable operator=(const Noncopyable){};
};

}//end of namespace sp

#endif
