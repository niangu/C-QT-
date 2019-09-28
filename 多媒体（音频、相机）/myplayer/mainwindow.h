#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMediaPlayer>
#include <QMainWindow>

class QMediaPlaylist;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;

private slots:
    void updatePosition(qint64 position);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void stateChanged(QMediaPlayer::State state);
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void showError(QMediaPlayer::Error error);
    void metaDataAvailableChanged(bool available);
};

#endif // MAINWINDOW_H
