#include <QCoreApplication>
#include<iostream>
#include"operation.h"
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int c,b;
    cin>>c>>b;
    COperation *op=CCalculatorFactory::Create('-');
    op->m_nFirst=c;
    op->m_nSecond=b;
    cout<<op->GetResult()<<endl;

    return a.exec();
}
