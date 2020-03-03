#include <QCoreApplication>
#include"request.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Manager *common=new CommonManager("张经理");
    Manager *major=new MajorDomo("李总监");
    common->SetSuccessor(major);
    Request *req=new Request();
    req->m_nNumber=33;
    common->GetRequest(req);
    req->m_nNumber=3;
    common->GetRequest(req);

    return a.exec();
}
