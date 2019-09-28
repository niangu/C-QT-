#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSoundEffect;
//视频
class QMediaPlayer;
class QVideoWidget;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QSoundEffect *effect;

    QMediaPlayer *player;
    QVideoWidget *videoWidget;
};

#endif // MAINWINDOW_H
