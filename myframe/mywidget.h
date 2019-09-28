#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

private slots:
    void on_pushBtn1_toggled(bool checked);

    void on_lineEdit_3_returnPressed();

    void on_pushButton_toggled(bool checked);

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
