#include "widget.h"
#include <QApplication>
#include "drawer.h"
#include"login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Drawer drawer;
    //drawer.resize(250,700);
    //drawer.show();
    login log;
    log.show();
    return a.exec();
}
