#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QLineEdit;
class QDialog;
class MySyntaxHighlighter;
class QPrinter;
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
    void on_action_New_triggered();

    void on_action_Dock_triggered();
    void setText(const QString &string);//向编辑器中添加文本
    void showTextFrame();//遍历文本框架
void showTextBlock();//遍历所有文本块
void setTextFont(bool checked);//设置字体格式
void insertTable();//插入表格
void insertList();//插入列表
void insertImage();//插入图片
void textFind();//查找文本
void findNext();//查找下一个
void doPrint();
void doPrintPreview();
void printPreview(QPrinter *printer);
void createPdf();
protected:
void dragEnterEvent(QDragEnterEvent *event);//拖动进入事件
void dropEvent(QDropEvent *event);//放下事件
//自定义拖放操作（图片）
//void mousePressEvent(QMouseEvent *event);//鼠标按下事件
//void dragMoveEvent(QDragMoveEvent *event);//拖动事件
private:
    Ui::MainWindow *ui;
    QLineEdit *lineEdit;
    QDialog *findDialog;
    MySyntaxHighlighter *highlighter;
};

#endif // MAINWINDOW_H
