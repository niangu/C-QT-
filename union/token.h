#ifndef TOKEN_H
#define TOKEN_H
#include<iostream>
//using namespace std;

class Token
{
public:
    //因为union含有一个string成员，所以Token必须定义拷贝控制成员
    //未定义移动构造函数和移动赋值运算符
    Token() : tok(INT),ival{0} {}
    Token(const Token &t) : tok(t.tok) {copyUnion(t);}
    Token &operator=(const Token&);
    //如果union含有一个string成员，则我们必须销毁它
    ~Token() {if (tok == STR) sval.~basic_string();}
    //下面的赋值运算符负责设置union的不同成员
    Token &operator=(const std::string&);
    Token &operator=(char);
    Token &operator=(int);
    Token &operator=(double);

private:
    enum{INT, CHAR, DBL, STR} tok; //判别式
    union{
        char cval;
        int ival;
        double dval;
        std::string sval;
    };//每个Token对象含有一个该未命名union类型的未命名成员
    //检查判别式，然后酌情拷贝union成员
    void copyUnion(const Token&);

};

#endif // TOKEN_H
