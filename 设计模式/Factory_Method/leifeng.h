#ifndef LEIFENG_H
#define LEIFENG_H
#include<string>
#include<iostream>
using namespace std;

//实例基类，相当于Product(为了方便没用抽象)
class LeiFeng
{
public:
    virtual void Sweep()
    {
        cout<<"雷锋扫地"<<endl;
    }
};
//学雷锋扫地大学生，相当于ConcreteProduct
class Student:public LeiFeng
{
public:
virtual void Sweep()
{
    cout<<"大学生扫地"<<endl;
}
};
//学雷锋的志愿者，相当于ConcreteProduct
class Volenter:public LeiFeng
{
    virtual void Sweep()
    {
        cout<<"志愿者"<<endl;
    }
};
//工厂基类Creator
class LeiFengFactory
{
public:
    virtual LeiFeng *CreateLeiFeng()
    {
        return new LeiFeng();
    }
};
//工厂具体类
class StudentFactory:public LeiFengFactory
{
public:
    virtual LeiFeng *CreateLeiFeng()
    {
        return new Student();
    }
};
class VolenterFactory:public LeiFengFactory
{
public:
    virtual LeiFeng *CreateLeiFeng()
    {
        return new Volenter();
    }
};

#endif // LEIFENG_H
