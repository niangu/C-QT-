#ifndef QTRSA_H
#define QTRSA_H

#include <QMainWindow>

namespace Ui {
class QtRSA;
}

class QtRSA : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtRSA(QWidget *parent = 0);
    ~QtRSA();
    QString  word;
private slots:
    void on_pushButton_jiami_clicked();

    void on_pushButton_jiemi_clicked();

    void on_pushButton_exit_clicked();


private:
    Ui::QtRSA *ui;
};

#endif // QTRSA_H
