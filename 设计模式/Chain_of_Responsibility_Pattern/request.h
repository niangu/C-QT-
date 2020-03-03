#ifndef REQUEST_H
#define REQUEST_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;
//责任链模式
//使多个对象都有机会处理请求，从而避免请求夫人发送者和接收者之间的耦合关系，将这个对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理为止

//请求
class Request
{
public:
    string m_strContent;
    int m_nNumber;
};
//管理者
class Manager
{
protected:
    Manager *manager;
    string name;
public:
    Manager(string temp)
    {
        name=temp;
    }
    void SetSuccessor(Manager *temp)
    {
        manager=temp;
    }
    virtual void GetRequest(Request* request)=0;
};
//经理
class CommonManager:public Manager
{
public:
    CommonManager(string strTemp):Manager(strTemp)
    {}
    virtual void GetRequest(Request* request)
    {
        if(request->m_nNumber>=0&&request->m_nNumber<10)
        {
            cout<<name<<"处理了"<<request->m_nNumber<<"个请求"<<endl;
        }else
        {
            manager->GetRequest(request);
        }
    }
};
//总监
class MajorDomo:public Manager
{
public:
    MajorDomo(string name):Manager(name){}
    virtual void GetRequest(Request *request)
    {
        if(request->m_nNumber>10)
        {
            cout<<name<<"处理了"<<request->m_nNumber<<"个请求"<<endl;
        }
    }
};

#endif // REQUEST_H
