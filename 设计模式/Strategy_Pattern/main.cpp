#include <QCoreApplication>
#include<iostream>
#include"coperation.h"
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
/*
    int d,b;
    char c;
    cin>>d>>b;
    cout<<"请输入运算符：";
    cin>>c;

    switch(c)
    {
    case '+':
        Context *context=new Context(new AddOperation(d,b));
        cout<<context->GetResult()<<endl;
       break;
    //default:
    }
*/
    int d,b;
    cin>>d>>b;
    Context *test=new Context('+');
    cout<<test->GetResult()<<endl;
    return a.exec();
}
