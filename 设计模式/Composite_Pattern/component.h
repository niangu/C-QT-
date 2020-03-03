#ifndef COMPONENT_H
#define COMPONENT_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;
//组合模式
//例一
class Component
{
public:
    string m_strName;
    Component(string strName)
    {
        m_strName=strName;
    }
    virtual void Add(Component* com)=0;
    virtual void Display(int nDepth)=0;
};

class Leaf:public Component
{
public:
    Leaf(string strName):Component(strName){}
    virtual void Add(Component* com)
    {
        cout<<"leaf can't add"<<endl;
    }
    virtual void Display(int nDepth)
    {
        string strtemp;
        for(int i=0;i<nDepth;i++)
        {
            strtemp+="-";
        }
        strtemp+=m_strName;
        cout<<strtemp<<endl;
    }
};
class Composite:public Component
{
private:
    vector<Component*>m_component;
public:
    Composite(string strName):Component(strName){}

    virtual void Add(Component* com)
    {
        m_component.push_back(com);
    }
    virtual void Display(int nDepth)
    {
        string strtemp;
        for(int i=0;i<nDepth;i++)
        {
            strtemp+="-";
        }
        strtemp+=m_strName;
        cout<<strtemp<<endl;
        vector<Component*>::iterator p=m_component.begin();
        while(p!=m_component.end())
        {
            (*p)->Display(nDepth+2);
            p++;
        }
    }
};

#endif // COMPONENT_H
