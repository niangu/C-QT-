#ifndef SINGELITON_H
#define SINGELITON_H

#endif // SINGELITON_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;
//单例模式
//保证一个类仅有一个实例，并且提供一个访问它的全局访问点
class SingeIton
{
private:
    SingeIton(){}
    static SingeIton *singel;
public:
    static SingeIton* GetInstance()
    {
        if(singel==NULL)
        {
            singel=new SingeIton();
        }
        return singel;
    }
};
SingeIton *SingeIton::singel=NULL;
