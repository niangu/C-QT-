#include <QCoreApplication>
#include"product.h"
#include"person.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /*
    //例一
    Direct *p=new Direct();
    Builder *b1=new ConcreteBuilder1();
    Builder *b2=new ConcreteBuilder2();

    p->Construct(b1); //调用第一种方式
    Product* pb1=b1->GetResult();
    pb1->Show();

    p->Construct(b2);//调用第二种方式
    Product *pb2=b2->GetResult();
    pb2->Show();
    */
    //例二
    Person *p=new FatPerson();
        Director *d= new Director(p);
        d->create();
        delete d;
        delete p;
        return 0;

    return a.exec();
}
