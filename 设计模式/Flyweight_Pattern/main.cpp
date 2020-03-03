#include <QCoreApplication>
#include"website.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WebFactory *f=new WebFactory();
    WebSite *ws=f->GetWeb();
    ws->Use();
    WebSite *ws2=f->GetWeb();
    ws2->Use();

    //不共享的类
    WebSite *ws3=new UnShareWebSite("测试");
    ws3->Use();

    return a.exec();
}
