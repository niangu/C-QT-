#ifndef HANDSETSOFT_H
#define HANDSETSOFT_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;
//桥接模式
//将抽象部分与实现部分分离，使它们可以独立变化
//手机软件
class HandsetSoft
{
public:
    virtual void Run()=0;
};
//游戏软件
class HandsetGame:public HandsetSoft
{
public:
    virtual void Run()
    {
        cout<<"运行手机游戏"<<endl;
    }
};
//通讯录软件
class HandSetAddressList:public HandsetSoft
{
public:
    virtual void Run()
    {
        cout<<"手机通讯录"<<endl;
    }
};
//手机品牌
class HandsetBrand
{
protected:
    HandsetSoft* m_soft;
public:
    void SetHandsetSoft(HandsetSoft* temp)
    {
        m_soft=temp;
    }
    virtual void Run()=0;
};
//M品牌
class HandsetBrandM:public HandsetBrand
{
public:
    virtual void Run()
    {
        m_soft->Run();
    }
};
//N品牌
class HandsetBrandN:public HandsetBrand
{
public:
    virtual void Run()
    {
                m_soft->Run();
     }
};


#endif // HANDSETSOFT_H
