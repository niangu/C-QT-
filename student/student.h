﻿#ifndef STUDENT_H
#define STUDENT_H

#include <QMainWindow>

namespace Ui {
class student;
}

class student : public QMainWindow
{
    Q_OBJECT

public:
    explicit student(QWidget *parent = 0);
    ~student();
    void init();
    QString stuName;
private slots:
    void on_pushButton_clicked();

private:
    Ui::student *ui;

};

#endif // STUDENT_H
