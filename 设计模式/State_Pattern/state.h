#ifndef STATE_H
#define STATE_H
#include<iostream>
using namespace std;
//状态模式
//当一个对象的行为取决于他的状态，并且它必须在运行时刻根据状态改变它的形为时，可考虑用到状态模式
class Work;
class ForenoonState;

class State
{
public:
    virtual void WriteProgram(Work* w)=0;
};
class Work
{
private:
    State *current;
public:
    double hour;

    Work();
    void SetState(State* temp)
    {
        current=temp;
    }
    void Writeprogram()
    {
        current->WriteProgram(this);
    }
};
class NoonState:public State
{
public:
    virtual void WriteProgram(Work* w)
    {
        cout<<"execute"<<endl;
        if((w->hour)<13)
            cout<<"还不错拉"<<endl;
        else
            cout<<"不行了，还是睡觉吧"<<endl;
    }
};
class ForenoonState:public State
{
public:
    virtual void WriteProgram(Work *w)
    {
        if((w->hour)<12)
            cout<<"现在的精神无敌好"<<endl;
        else{
            w->SetState(new NoonState());
            w->Writeprogram();//注意加上这句
        }
    }
};
Work::Work()
{
    current=new ForenoonState();
}


#endif // STATE_H
