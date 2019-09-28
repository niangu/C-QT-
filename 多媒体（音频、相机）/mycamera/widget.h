#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QMediaRecorder;
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;
    QMediaRecorder *recorder;
};

#endif // WIDGET_H
