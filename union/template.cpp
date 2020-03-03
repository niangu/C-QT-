#include "template.h"
#include<string>
#include<iostream>
using namespace std;


//定义静态成员
template <typename T>
std::size_t  Blob<T>::ctr = 0;
template <typename T>
Blob<T>::Blob():data(std::make_shared<vector<T>>()) { }
template<typename T>
Blob<T>::Blob(std::initializer_list<T> il):data(make_shared<vector<T>>(il)) { }

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if(i>=data->size())
        throw std::out_of_range(msg);
}
template<typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}
template<typename T>
T& Blob<T>::operator[](size_type i)
{
    //如果i太大会抛出异常，阻止访问一个不存在的元素
    check(i, "subscript out of range");
    return (*data)[i];
}
template<typename T>
void Blob<T>::pop_back()
{
check(0, "pop_back on empty Blob");
data->pop_back();
}



/*
//多个重载函数定义模板
int compare(const string &v1, const string &v2)
{
    if(v1<v2) return -1;
    if(v2<v1) return 1;
    return 0;
}
int compare(const  double &v1, const double &v2)
{
    if(v1<v2) return -1;
    if(v2<v1) return 1;
    return 0;
 }
*/


