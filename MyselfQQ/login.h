#ifndef LOGIN_H
#define LOGIN_H
#include"admin.h"
#include <QMainWindow>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_login_clicked();

private:
    Ui::login *ui;
    admin *adm;
};

#endif // LOGIN_H
