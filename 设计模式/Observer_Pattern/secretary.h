#ifndef SECRETARY_H
#define SECRETARY_H
#include<string>
#include<iostream>
#include<vector>
using namespace std;

class Secretary;
//看股票的同事类（观察对象，观察者）
class StockObserver
{
private:
    string name;
    Secretary* sub;
public:
    StockObserver(string strname,Secretary* strsub)
    {
        name=strname;
        sub=strsub;
    }
    void Update();
};
//秘书类（主题对象，通知者）
class Secretary
{
private:
    vector<StockObserver>observers;
public:
    string action;
    void Add(StockObserver ob)
    {
        observers.push_back(ob);
    }
    void Notify()
    {
        vector<StockObserver>::iterator p=observers.begin();
        while(p!=observers.end())
        {
            (*p).Update();
            p++;
        }
    }

};
void StockObserver::Update()
{
    cout<<name<<":"<<sub->action<<",不玩股票了，要开始工作了"<<endl;
}
#endif // SECRETARY_H
