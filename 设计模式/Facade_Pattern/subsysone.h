#ifndef SUBSYSONE_H
#define SUBSYSONE_H
#include<iostream>
using namespace std;
class SubSysOne
{
public:
    void MethodOne()
    {
        cout<<"方法一"<<endl;
    }
};

class SubSysTwo
{
public:
    void MethodTwo()
    {
        cout<<"方法二"<<endl;
    }
};
class SubSysThree
{
public:
    void MethodThree()
    {
        cout<<"方法三"<<endl;
    }
};
//外观类
class Facade
{
private:
    SubSysOne* sub1;
    SubSysTwo* sub2;
    SubSysThree* sub3;
public:
    Facade()
    {
        sub1=new SubSysOne();
        sub2=new SubSysTwo();
        sub3=new SubSysThree();
    }
    ~Facade()
    {
        delete sub1;
        delete sub2;
        delete sub3;
    }
    void FacadeMethod()
    {
        sub1->MethodOne();
        sub2->MethodTwo();
        sub3->MethodThree();
    }
};

#endif // SUBSYSONE_H
