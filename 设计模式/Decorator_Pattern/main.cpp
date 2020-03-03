#include <QCoreApplication>
#include"person.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Person *p=new Person("小李");
    BigTrouser *bt=new BigTrouser();
    TShirts *ts=new TShirts();

    bt->Decorate(p);
    ts->Decorate(bt);
    ts->Show();

    return a.exec();
}
