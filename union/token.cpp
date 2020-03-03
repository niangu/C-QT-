#include "token.h"


Token &Token::operator=(int i)
{
    if (tok == STR) sval.~basic_string();
    ival = i; //为成员赋值
    tok = INT;//更新判别式
    return *this;
}
Token &Token::operator=(const std::string &s)
{
    if (tok == STR)
        sval = s;
    else
        new(&sval) std::string(s);
    tok = STR;
    return *this;
}
void Token::copyUnion(const Token &t)
{
    switch(t.tok){
    case Token::INT: ival = t.ival; break;
    case Token::CHAR: cval = t.cval; break;
    case Token::DBL: dval = t.dval; break;
    //要想拷贝一个string可以使用定位new表达式构造它
    case Token::STR: new(&sval) std::string(t.sval); break;
    }
}

Token &Token::operator=(const Token &t)
{
 //如果此对象的值是string而t的值不是，则我们必须释放原来的string
 if (tok==STR && t.tok !=STR) sval.~basic_string();
 if (tok==STR && t.tok !=STR)
     sval = t.sval; //无需构造一个新string
 else
     copyUnion(t);//如果t.tok是STR,则需要构造一个string
 tok = t.tok;
 return *this;
}
