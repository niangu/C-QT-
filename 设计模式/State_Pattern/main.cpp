#include <QCoreApplication>
#include"state.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Work *mywork=new Work();
    mywork->hour=9;
    mywork->Writeprogram();
    mywork->hour=14;
    mywork->Writeprogram();
    return a.exec();
}
