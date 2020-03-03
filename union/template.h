#ifndef TEMPLATE_H
#define TEMPLATE_H
#include<vector>
#include<memory>
#include<string.h>
#include<ostream>
template <typename T> class Blob{
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    //构造函数
    Blob();
    Blob(std::initializer_list<T> il);
    //Blob中元素的数目
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    //添加和删除元素
    void push_back(const T &t) {data->push_back(t);}
    //移动版本
    void push_back(T &&t) {data->push_back(std::move(t));}
    void pop_back();
    //元素访问
    T& back();
    T& operator[] (size_type i);
    //静态成员
    static std::size_t ctr;

private:
    std::shared_ptr<std::vector<T>> data;
    //若data[i]无效，则抛出msg
    void check(size_type i,const std::string &msg) const;
};


template <typename T>
int compare(const T &v1,const T &v2)
{
    if(v1<v2) return -1;
    if(v2<v1) return 1;
    return 0;
}
//非类型模板参数
template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}

template <typename T> inline T min(const T&,const T&);

//定义函数模板特例化
template <>
int compare(const char* const &p1, const char* const &p2)
{
    return strcmp(p1, p2);
}

//类模板实例化
//类模板特例化必须在原模板的命名空间中特例化
//命名空间后面没有分号
class Sales_data;
namespace std{
template<>
struct hash<Sales_data>
{
};
}

//可变形参
template<typename T, typename... Args>
std::ostream& print(std::ostream &os, const T &t, const Args&... reset) //扩展Args
{
    os<<t<<", ";
    return print(os, reset...);  //扩展reset
}
//定义能保存类型信息的函数参数
template<typename F, typename T1, typename T2>
void flip(F f,T1 &&t1,T2 &&t2)
{
    f(t2, t1);
}
//在调用中使用std::forward保存类型信息
template<typename F, typename T1, typename T2>
void flip_2(F f, T1 &&t1, T2 &&t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

#endif // TEMPLATE_H
