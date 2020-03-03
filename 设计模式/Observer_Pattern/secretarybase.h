#ifndef SECRETARYBASE_H
#define SECRETARYBASE_H
#include<string>
#include<iostream>
#include<vector>
using namespace std;

class SecretaryBase;
//抽象观察者
class CObserverBase
{
protected:
    string name;
    SecretaryBase* sub;
public:
    CObserverBase(string strname,SecretaryBase* strsub)
    {
        name=strname;
        sub=strsub;
    }
    virtual void Update()=0;
};
//具体的观察者，看股票的
class StockObserver:public CObserverBase
{
public:
    StockObserver(string strname,SecretaryBase* strsub):CObserverBase(strname,strsub)
    {

    }
    virtual void Update();
};
//具体观察者，看NBA的
class NBAObserver:public CObserverBase
{
public:
    NBAObserver(string strname, SecretaryBase* strsub):CObserverBase(strname,strsub){}
    virtual void Update();
};
//抽象通知者
class SecretaryBase
{
public:
    string action;
    vector<CObserverBase*>observers;
    virtual void Attach(CObserverBase* observer)=0;
    virtual void Notify()=0;

};
//具体通知者
class Secretary:public SecretaryBase{
public:
    void Attach(CObserverBase *ob)
    {
        observers.push_back(ob);
    }
    void Notify()
    {
        vector<CObserverBase*>::iterator p=observers.begin();
        while (p!=observers.end()) {
            (*p)->Update();
            p++;
        }
    }
};
void StockObserver::Update()
{
    cout<<name<<":"<<sub->action<<",不要玩股票了，要开始工作理"<<endl;
}
void NBAObserver::Update()
{
    cout<<name<<":"<<sub->action<<"不要看NBA了，老板来了"<<endl;
}
#endif // SECRETARYBASE_H
