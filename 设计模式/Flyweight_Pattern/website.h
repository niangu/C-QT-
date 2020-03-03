#ifndef WEBSITE_H
#define WEBSITE_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;

//抽象的网站
class WebSite
{
public:
    virtual void Use()=0;
};
//具体的共享网站
class ConcreteWebSite:public WebSite
{
private:
    string name;
public:
    ConcreteWebSite(string strName)
    {
        name=strName;
    }
    virtual void Use()
    {
        cout<<"网站分类:"<<name<<endl;
    }
};
//不共享的网站
class UnShareWebSite:public WebSite
{
private:
    string name;
public:
    UnShareWebSite(string strName)
    {
        name=strName;
    }
    virtual void Use()
    {
        cout<<"不共享的网站:"<<name<<endl;
    }
};
//网站工厂类，用于存放共享的WebSite对象
class WebFactory
{
private:
    vector<WebSite*>websites;
public:
    WebSite* GetWeb()
    {
        vector<WebSite*>::iterator p=websites.begin();
        return *p;
    }
    WebFactory()
    {
        websites.push_back(new ConcreteWebSite("测试"));
    }
};


#endif // WEBSITE_H
