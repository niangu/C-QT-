#include <QCoreApplication>
#include"abstractexpression.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Context *context=new Context();
    vector<AbstractExpression*>express;
    express.push_back(new Expression());
    express.push_back(new NonterminalExpression());
    express.push_back(new NonterminalExpression());

    vector<AbstractExpression*>::iterator p=express.begin();
    while(p!=express.end())
    {
        (*p)->Interpret(context);
        p++;
    }
    return a.exec();
}
