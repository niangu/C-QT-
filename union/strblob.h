#ifndef STRBLOB_H
#define STRBLOB_H

#include<string>
#include<vector>
#include<memory>

class StrBlobPtr;
class StrBlob
{

public:
    friend StrBlobPtr;
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size();}
    bool empty() const {return data->empty();}
    //添加和删除元素
    void push_back(const std::string &t){data->push_back(t);}
    void pop_back();
    //元素访问
    std::string& front();
    std::string& back();
    //返回指向首元素和尾后元素的StrBlobPtr
    StrBlobPtr begin();
    StrBlobPtr end();

private:
    std::shared_ptr<std::vector<std::string>> data;
    //如果data[i]不合法抛出一个异常
    void check(size_type i, const std::string &msg) const;
};

#endif // STRBLOB_H
