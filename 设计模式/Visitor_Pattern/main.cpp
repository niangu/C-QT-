#include <QCoreApplication>
#include"action.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ObjectStructure *os=new ObjectStructure();
    os->Add(new Man());
    os->Add(new Woman());

    Success *success=new Success();
    os->Display(success);

    Failure *fl=new Failure();
    os->Display(fl);

    return a.exec();
}
