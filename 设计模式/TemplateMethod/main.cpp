#include <QCoreApplication>
#include"abstractclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Naruto *man=new Naruto();
    man->Show();

    OnePice *man2=new OnePice();
    man2->Show();
    return a.exec();
}
