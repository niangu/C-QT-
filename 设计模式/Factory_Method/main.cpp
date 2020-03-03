#include <QCoreApplication>
#include"leifeng.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LeiFengFactory *sf=new LeiFengFactory();
    LeiFeng *s=sf->CreateLeiFeng();
    s->Sweep();
    delete s;
    delete sf;
    return 0;

    return a.exec();
}
