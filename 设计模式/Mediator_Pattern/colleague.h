#ifndef COLLEAGUE_H
#define COLLEAGUE_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Colleague;
//中介者类
class Mediator
{
public:
    virtual void Send(string message,Colleague* col)=0;
};
//抽象同事类
class Colleague
{
protected:
    Mediator *mediator;
public:
    Colleague(Mediator* temp)
    {
        mediator=temp;
    }
};
//同事一
class Colleague1:public Colleague
{
public:
    Colleague1(Mediator *media):Colleague(media){}
    void Send(string strMessage)
    {
        mediator->Send(strMessage,this);
    }
    void Notify(string strMessage)
    {
        cout<<"同事一获得了消息"<<strMessage<<endl;
    }
};
//同事二
class Colleague2:public Colleague
{
public:
    Colleague2(Mediator *media):Colleague(media){}
    void Send(string strMessage)
    {
        mediator->Send(strMessage,this);
    }
    void Notify(string strMessage)
    {
        cout<<"同事二获得了消息"<<strMessage<<endl;
    }
};
//具体中介类
class ConcreteMediator:public Mediator
{
public:
    Colleague1 *col1;
    Colleague2 *col2;
    virtual void Send(string message,Colleague *col)
    {
        if(col==col1)
            col2->Notify(message);
        else
            col1->Notify(message);
    }
};

#endif // COLLEAGUE_H
