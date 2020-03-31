#ifndef MD5_CHECK_H
#define MD5_CHECK_H

#include <QMainWindow>

namespace Ui {
class MD5_check;
}

class MD5_check : public QMainWindow
{
    Q_OBJECT

public:
    explicit MD5_check(QWidget *parent = 0);
    ~MD5_check();
     QString MyMD5;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_createMD5_clicked();

    void on_pushButton_createMD5ofFile_clicked();

    void on_pushButton_check_clicked();

private:
    Ui::MD5_check *ui;

};

#endif // MD5_CHECK_H
