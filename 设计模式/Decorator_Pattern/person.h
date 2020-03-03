#ifndef PERSON_H
#define PERSON_H
#include<string>
#include<iostream>
using namespace std;
//装饰模式
//动态的给一个对象添加一些额外的职责（不重要的功能，值时偶然一次要执行）

class Person
{
private:
    string m_strName;
public:
    Person(string strName)
    {
        m_strName=strName;
    }
    Person(){}
    virtual void Show()
    {
        cout<<"装扮的是:"<<m_strName<<endl;
    }
};

//装饰类
class Finery:public Person
{
protected:
    Person *m_component;
public:
    void Decorate(Person *component)
    {
        m_component=component;
    }
    virtual void Show()
    {
        m_component->Show();
    }
};

class TShirts:public Finery
{
public:
    virtual void show()
    {
        cout<<"T Shirts"<<endl;
        m_component->Show();
    }
};

class BigTrouser:public Finery
{
public:
    virtual void show()
    {
        cout<<"Big Trouser"<<endl;
        m_component->Show();
    }
};

#endif // PERSON_H
