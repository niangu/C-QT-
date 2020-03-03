#include <QCoreApplication>
#include"interface.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ProxyClass *test=new ProxyClass();
    test->Request();

    return a.exec();
}
