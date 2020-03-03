#ifndef ABSTRACTEXPRESSION_H
#define ABSTRACTEXPRESSION_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Context;
class AbstractExpression
{
public:
    virtual void Interpret(Context *context)=0;
};
class Expression:public AbstractExpression
{
public:
    virtual void Interpret(Context *context)
    {
        cout<<"终端解释器"<<endl;
    }
};
class NonterminalExpression:public AbstractExpression
{
public:
    virtual void Interpret(Context* context)
    {
        cout<<"非终端解释器"<<endl;
    }
};
class Context
{
public:
    string input;
    string output;
};


#endif // ABSTRACTEXPRESSION_H
