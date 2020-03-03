#include <QCoreApplication>
//#include"secretary.h"
#include"secretarybase.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /*
    Secretary *p=new Secretary();//创建建造者

    //观察者
    StockObserver *s1=new StockObserver("小李",p);
    StockObserver *s2=new StockObserver("小赵",p);
    //加入通知队列
    p->Add(*s1);
    p->Add(*s2);
    //事件
    p->action="老板来了";
    //通知
    p->Notify();
    */
    SecretaryBase *p=new Secretary();//创建观察者

    //被观察的对象
    CObserverBase *s1=new NBAObserver("小李",p);
    CObserverBase *s2=new StockObserver("小赵",p);
    //加入观察队列
    p->Attach(s1);
    p->Attach(s2);
    //事件
    p->action="老板来了";
    //通知
    p->Notify();
    return a.exec();
}
