#ifndef PRODUCT_H
#define PRODUCT_H
#include<string>
#include<iostream>
#include<vector>
using namespace std;
//在当创建复杂对象的算法应该独立于该对象的组成部分以及它们的装配方式时适用
//建造者模式例一
//最终产品类
class Product
{
private:
    vector<string>m_product;
public:
    void Add(string strtemp)
    {
        m_product.push_back(strtemp);
    }
    void Show()
    {
        vector<string>::iterator p=m_product.begin();
        while(p!=m_product.end())
        {
            cout<<*p<<endl;
            p++;
        }
    }
};
//建造者基类
class Builder
{
public:
    virtual void BuilderA()=0;
    virtual void BuilderB()=0;
    virtual Product *GetResult()=0;
};
//第一种建造方式
class ConcreteBuilder1:public Builder
{
private:
    Product *m_product;
public:
    ConcreteBuilder1()
    {
        m_product=new Product();
    }
    virtual void BuilderA()
    {
        m_product->Add("one");
    }
    virtual void BuilderB()
    {
        m_product->Add("two");
    }
    virtual Product* GetResult()
    {
        return m_product;
    }
};
//第二种建造方式
class ConcreteBuilder2:public Builder
{
 private:
    Product *m_product;
public:
    ConcreteBuilder2()
    {
        m_product=new Product();
    }
    virtual void BuilderA()
    {
        m_product->Add("A");
    }
    virtual void BuilderB()
    {
        m_product->Add("B");
    }
    virtual Product* GetResult()
    {
        return m_product;
    }
};
//指挥者类
class Direct
{
public:
    void Construct(Builder* temp)
    {
        temp->BuilderA();
        temp->BuilderB();
    }
};

#endif // PRODUCT_H
