#include "strblobptr.h"

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i,const std::string &msg) const
{
 auto ret = wptr.lock();//vector还存在吗
 if(!ret)
     throw std::runtime_error("unbound StrBlobPtr");
 if (i>=ret->size())
     throw std::out_of_range(msg);
 return ret;//否则，返回指向vector的shared_ptr
}

std::string& StrBlobPtr::deref() const
{
    auto p = check(curr,"dereference past end");
    return (*p)[curr];//（*p)是对象所指向的vector
}

//前缀递增：返回递增后的对象的引用
StrBlobPtr& StrBlobPtr::incr()
{
    //如果curr已经指向容器的尾后位置，就不能递增它
    check(curr,"increment past end of StrBlobPtr");
    ++curr;//推进当前位置
    return *this;
}

