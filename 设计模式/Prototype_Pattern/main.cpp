#include <QCoreApplication>
#include"prototype.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ConcretePrototype1 *test=new ConcretePrototype1("小王");
    ConcretePrototype2 *test2=(ConcretePrototype2*)test->Clone();
    test->Show();
    test2->Show();
    return a.exec();
}
