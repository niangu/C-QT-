#include <QCoreApplication>
#include"subsysone.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Facade *test=new Facade();
    test->FacadeMethod();

    return a.exec();
}
