//工厂模式
//工厂类和基类为关联关系
//核心思想用一个工厂来根据输入的条件产生不同的类，根据不同类的viryual函数得到不同的结果

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
//加法
class AddOperation:public COperation
{
public:
    virtual double GetResult()
    {
        return m_nFirst+m_nSecond;
    }
};
//减法
class SubOperation:public COperation
{
public:
    virtual double GetResult()
    {
        return m_nFirst-m_nSecond;
    }
};
//工厂类
class CCalculatorFactory
{
public:
    static COperation* Create(char cOperator);
};

COperation* CCalculatorFactory::Create(char cOperator)
{
    COperation *oper;
    switch(cOperator)
    {
    case '+':
        oper=new AddOperation();
        break;
    case '-':
        oper=new SubOperation();
        break;
    default:
        oper=new AddOperation();
        break;
    }
    return oper;
}
