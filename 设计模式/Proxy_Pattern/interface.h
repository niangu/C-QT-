#ifndef INTERFACE_H
#define INTERFACE_H
#include<string>
#include<iostream>
using namespace std;

//定义接口
class Interface
{
public:
    virtual void Request()=0;
};
//真实类
class RealClass:public Interface
{
public:
    virtual void Request()
    {
        cout<<"真实的请求"<<endl;
    }
};
//代理类
class ProxyClass:public Interface
{
private:
    RealClass *m_realClass;
public:
    virtual void Request()
    {
        m_realClass=new RealClass();
        m_realClass->Request();
        delete m_realClass;
    }
};

#endif // INTERFACE_H
