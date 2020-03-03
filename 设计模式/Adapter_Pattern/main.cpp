#include <QCoreApplication>
#include"target.h"
#include"player.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Adapter *ada=new Adapter();
    ada->Request();
    delete ada;
    //例二
    Player *p=new TransLater("小李");
    p->Attack();
    return a.exec();
}
