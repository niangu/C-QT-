#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//建造者模式例二
class Person
{
public:
    virtual void createHead()=0;
    virtual void createHand()=0;
    virtual void createBody()=0;
    virtual void createFoot()=0;
};

class ThinPerson:public Person
{
    void createHead()
    {
        cout<<"thin head"<<endl;
    }
    void createHand()
    {
        cout<<"thin hand"<<endl;
    }
    void createBody()
    {
        cout<<"thin body"<<endl;
    }
    void createFoot()
    {
        cout<<"thin foot"<<endl;
    }
};

class FatPerson:public Person
{
    void createHead()
    {
        cout<<"fat head"<<endl;
    }
    void createHand()
    {
        cout<<"fat hand"<<endl;
    }
    void createBody()
    {
        cout<<"fat body"<<endl;
    }
    void createFoot()
    {
        cout<<"fat foot"<<endl;
    }
};


class Director
{
private:
    Person *p;
public:
    Director(Person *temp)
    {
        p=temp;
    }
    void create()
    {
        p->createHead();
        p->createHand();
        p->createBody();
        p->createFoot();
    }
};
#endif // PERSON_H
