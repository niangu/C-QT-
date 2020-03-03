#ifndef TARGET_H
#define TARGET_H
#include<iostream>
using namespace std;
//适配器模式
//例二
//双方都不适合修改的时候，可以考虑使用适配器模式
class Target
{
public:
    virtual void Request()
    {
        cout<<"普通的请求"<<endl;
    }
};
class Adaptee
{
public:
    void SpecificalRequest()
    {
        cout<<"特殊请求"<<endl;
    }
};
class Adapter:public Target
{
private:
    Adaptee *ada;
public:
    virtual void Request()
    {
        ada->SpecificalRequest();
        Target::Request();
    }
    Adapter()
    {
        ada=new Adaptee();
    }
    ~Adapter()
    {
        delete ada;
    }
};

#endif // TARGET_H
