#include <QCoreApplication>
#include"memo.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Originator *on=new Originator();
    on->state="on";
    on->Show();

    Caretaker *c=new Caretaker();
    c->memo=on->CreateMemo();

    on->state="off";
    on->Show();

    on->SetMemo(c->memo);
    on->Show();
    return a.exec();
}
