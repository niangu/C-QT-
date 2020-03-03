#ifndef COPERATION_H
#define COPERATION_H

//策略模式
//定义算法家族，分别封装起来，让它们之间可以相互替换，让算法变化，不会影响到用户
class COperation
{
public:
    int m_nFirst;
    int m_nSecond;
    virtual double GetResult()
    {
        double dResult=0;
        return dResult;
    }
};

//策略具体类-加法类
class AddOperation: public COperation
{
public:
    AddOperation(int a,int b)
    {
        m_nFirst=a;
        m_nSecond=b;
    }
    AddOperation()
    {}
    virtual double GetResult()
    {
        return m_nFirst+m_nSecond;
    }
};
/*
class Context
{
private:
    COperation *op;
public:
    Context(COperation *temp)
    {
        op=temp;
    }
    double GetResult()
    {
        return op->GetResult();
    }
};
*/
//策略与工厂结合, 客户端只需访问Context类，而不用知道其他任何类信息，实现了低耦合
 class Context
 {
 private:
     COperation *op;
 public:
     Context(char cType)
     {
         switch(cType)
         {
         case '+':
             op=new AddOperation(3,8);
             break;
         default:
             op=new AddOperation();
             break;
         }
     }
     double GetResult()
     {
         return op->GetResult();
     }
 };


#endif // COPERATION_H
