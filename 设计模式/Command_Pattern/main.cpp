#include <QCoreApplication>
#include"barbucer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //店里添加烤肉师傅，菜单，服务员等顾客
    Barbucer *barbucer=new Barbucer();
    Command *cmd=new BakeMuttonCmd(barbucer);
    Command *cmd2=new ChickenWingCmd(barbucer);
    Waiter *girl=new Waiter();
    //点菜
    girl->SetCmd(cmd);
    girl->SetCmd(cmd2);
    //服务员通知
    girl->Notify();
    return a.exec();
}
