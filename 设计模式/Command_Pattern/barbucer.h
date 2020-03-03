#ifndef BARBUCER_H
#define BARBUCER_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;
//命令模式
//一建立命令队列，二可以将命令记入日志，三接收请求的一方可以拒绝，四添加一个新命令类不影响其他类
//烤肉师傅
class Barbucer
{
public:
    void MakeMutton()
    {
        cout<<"烤羊肉"<<endl;
    }
    void MakeChickenWing()
    {
        cout<<"烤鸡翅膀"<<endl;
    }
};
//抽象命令类
class Command
{
protected:
    Barbucer* receiver;
public:
    Command(Barbucer*temp)
    {
        receiver=temp;
    }
    virtual void ExecuteCmd()=0;
};
//烤羊肉命令
class BakeMuttonCmd:public Command
{
public:
    BakeMuttonCmd(Barbucer *temp):Command(temp){}
    virtual void ExecuteCmd()
    {
     receiver->MakeMutton();
    }
};
//烤鸡翅
class ChickenWingCmd:public Command
{
public:
    ChickenWingCmd(Barbucer *temp):Command(temp){}
    virtual void ExecuteCmd()
    {
        receiver->MakeChickenWing();
    }
};
//服务员类
class Waiter
{
protected:
    vector<Command*>m_commandList;
public:
    void SetCmd(Command *temp)
    {
        m_commandList.push_back(temp);
        cout<<"增加定单"<<endl;
    }
    //通知执行
    void Notify()
    {
        vector<Command*>::iterator p=m_commandList.begin();
        while(p!=m_commandList.end())
        {
            (*p)->ExecuteCmd();
            p++;
        }
    }
};


#endif // BARBUCER_H
