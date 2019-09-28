#include "regexpplugin.h"
#include<QRegExp>
#include<QtPlugin>
RegExpPlugin::RegExpPlugin()
{}

QString RegExpPlugin::regexp(const QString &message)
{
   QRegExp rx("\\d+");
   rx.indexIn(message);
   QString str=rx.cap(0);
   return str;
}
