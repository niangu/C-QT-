#include <QCoreApplication>
#include"colleague.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ConcreteMediator *m=new ConcreteMediator();

    //让同事认识中介
    Colleague1 *col1=new Colleague1(m);
    Colleague2 *col2=new Colleague2(m);
    //让中介认识具体的同事类
    m->col1=col1;
    m->col2=col2;

    col1->Send("吃饭了吗?");
    col2->Send("还没吃,你请吗?");
    return a.exec();
}
