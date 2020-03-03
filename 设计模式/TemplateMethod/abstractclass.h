#ifndef ABSTRACTCLASS_H
#define ABSTRACTCLASS_H
#include<iostream>
#include<vector>
#include<string>
using namespace std;

//模板方法模式，把不变的放到父类，把变化的放到子类
class AbstractClass
{
public:
    void Show()
    {
        cout<<"我是"<<GetName()<<endl;
    }
protected:
    virtual string GetName()=0;
};

class Naruto:public AbstractClass
{
protected:
    virtual string GetName()
    {
        return "火影史上最帅的六代目-";
    }
};

class OnePice:public AbstractClass
{
protected:
    virtual string GetName()
    {
        return "我是无恶不做的大海盗";
    }
};

#endif // ABSTRACTCLASS_H
