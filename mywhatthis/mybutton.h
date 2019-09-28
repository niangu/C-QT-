#ifndef MYBUTTON_H
#define MYBUTTON_H

#include<QPushButton>


class MyButton : public QPushButton
{
    Q_OBJECT
public://提升窗口部件
   explicit MyButton(QWidget *parent=0);
    QString getName(){return "My Button!";}
};

#endif // MYBUTTON_H

