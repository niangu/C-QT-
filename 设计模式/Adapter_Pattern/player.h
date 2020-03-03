#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include<string>
using namespace std;
//例二
class Player
{
protected:
    string name;
public:
    Player(string strName){name=strName;}
    virtual void Attack()=0;
    virtual void Defense()=0;
};
class Forwards:public Player
{
public:
    Forwards(string strName):Player(strName){}

    virtual void Attack()
    {
        cout<<name<<"前锋进攻"<<endl;
    }
    virtual void Defense()
    {
        cout<<name<<"前锋防守"<<endl;
    }
};
class Center:public Player
{
public:
    Center(string strName):Player(strName){}
public:
    virtual void Attack()
    {
        cout<<name<<"中场进攻"<<endl;
    }
    virtual void Defense()
    {
        cout<<name<<"中场防守"<<endl;
    }
};
//为中场翻译
class TransLater:public Player
{
private:
    Center *player;
public:
    TransLater(string strName):Player(strName)
    {
        player=new Center(strName);
    }
    virtual void Attack()
    {
        player->Attack();
    }
    virtual void Defense()
    {
        player->Defense();
    }
};

#endif // PLAYER_H
