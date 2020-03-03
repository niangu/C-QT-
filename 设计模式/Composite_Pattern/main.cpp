#include <QCoreApplication>
#include"component.h"
#include"company.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /*
    //例一
    Composite *p=new Composite("小王");
    p->Add(new Leaf("小李"));
    p->Add(new Leaf("小赵"));

    Composite *p1=new Composite("小五");
    p1->Add(new Leaf("大三"));
     p->Add(p1);
     p->Display(1);
     */
     //例二
     ConcreteCompany *p=new ConcreteCompany("清华大学");
     p->Add(new HrDepartment("清华大学人才部"));

     ConcreteCompany *p1=new ConcreteCompany("数学系");
     p1->Add(new HrDepartment("数学系人才部"));

     ConcreteCompany *p2=new ConcreteCompany("物理系");
     p2->Add(new HrDepartment("物理系人才部"));

     p->Add(p1);
     p->Add(p2);

     p->Display(1);
     p->LineOfDuty();
    return a.exec();
}
