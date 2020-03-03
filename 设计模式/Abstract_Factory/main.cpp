#include <QCoreApplication>
#include<string>
#include<vector>
#include"iuser.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    IFactory* factory=new SqlFactory();
    IUser* user=factory->CreateUser();
    IDepartment* depart=factory->CreateDepartment();
    user->GetUser();
    depart->GetDepartment();
    return 0;

    return a.exec();
}
