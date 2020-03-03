#include <QCoreApplication>
#include"singeliton.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SingeIton *s1=SingeIton::GetInstance();
    SingeIton *s2=SingeIton::GetInstance();
    if(s1==s2)
        cout<<"ok"<<endl;
    else
        cout<<"no"<<endl;

    return a.exec();
}
