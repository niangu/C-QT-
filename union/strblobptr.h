#ifndef STRBLOBPTR_H
#define STRBLOBPTR_H

#include<memory>
#include<string>
#include<vector>
#include"strblob.h"
//StrBlobPtr为StrBlob的伴随指针类

class StrBlobPtr
{
public:
    StrBlobPtr():curr(0){}
    StrBlobPtr(StrBlob &a,size_t sz=0):wptr(a.data),curr(sz){}
    std::string& deref() const;
    StrBlobPtr& incr();//前缀递增

private:
    //若检查成功,check返回一个指向vector的shared_ptr
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;//在数组中的当前位置
};

#endif // STRBLOBPTR_H
