#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QToolButton>
#include<QSpinBox>
#include<QTextEdit>
#include<QMdiSubWindow>
#include<QLabel>
#include"myaction.h"
#include<QMenu>
#include<QTextFrame>
#include<QDebug>
#include<QLineEdit>
#include<QDialog>
#include<QPushButton>
#include<QVBoxLayout>
#include"mysyntaxhighlighter.h"
#include<QDragEnterEvent>
#include<QUrl>
#include<QFile>
#include<QTextStream>
#include<QMimeData>
#include<QMouseEvent>
#include<QDragMoveEvent>
#include<QDropEvent>
#include<QDrag>
#include<QPainter>
#include<QPrintDialog>
#include<QPrintPreviewDialog>
#include<QFileDialog>
#include<QFileInfo>
#include<QPrinter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*
    //编辑菜单
   QMenu *editMenu=ui->menuBar->addMenu(tr("编辑(&E)"));//添加编辑菜单
    QAction *action_Open=editMenu->addAction(QIcon(":/image/images/Open.png"),tr("打开文件(&O)"));//添加打开菜单
    action_Open->setShortcut(QKeySequence("Ctrl+O"));//设置快捷键
    ui->mainToolBar->addAction(action_Open);//在工具栏中添加动作
//动作组
    QActionGroup *group=new QActionGroup(this);//建立动作组
    QAction *action_L=group->addAction(tr("左对齐(&L)"));//向动作组中添加动作
    action_L->setCheckable(true);//设置动作checkable属性为true
    QAction *action_R=group->addAction(tr("右对齐(&R)"));
    action_R->setCheckable(true);
    QAction *action_C=group->addAction(tr("居中(&C)"));
    action_C->setCheckable(true);
    action_L->setCheckable(true);//最后指定action_L为选中状态
    editMenu->addSeparator();
   editMenu->addAction(action_L);
    editMenu->addAction(action_R);
  editMenu->addAction(action_C);
*/
//向工具栏添加控件
    QToolButton *toolBtn=new QToolButton(this); //创建QToolButton
toolBtn->setText(tr("颜色"));
QMenu *colorMenu=new QMenu(this);//创建一个菜单
colorMenu->addAction(tr("红色"));
colorMenu->addAction(tr("绿色"));
toolBtn->setMenu(colorMenu);//添加菜单
toolBtn->setPopupMode(QToolButton::MenuButtonPopup);//设置弹出模式
ui->mainToolBar->addWidget(toolBtn);//向工具栏添加QToolButton按钮
QSpinBox *spinBox=new QSpinBox(this);//创建QSpinBox
ui->mainToolBar->addWidget(spinBox);//向工具栏添加QSpinBox部件

//显示临时消息，显示2000毫秒即2秒
ui->statusBar->showMessage(tr("欢迎使用多文档编辑器"),2000);
//创建标签，设置标签样式并显示信息，然后将其以永久部件的形式添加到状态栏
QLabel *permanent=new QLabel(this);
permanent->setFrameStyle(QFrame::Box|QFrame::Sunken);
permanent->setText("www.qter.org");
ui->statusBar->addPermanentWidget(permanent);

//自定义菜单
//添加菜单并且加入我们的action
MyAction *action=new MyAction;
QMenu *editMenu=ui->menuBar->addMenu(tr("编辑(&E)"));
editMenu->addAction(action);
//将action的getText()信号和这里的setText()槽进行关联
connect(action,SIGNAL(getText(QString)),this,SLOT(setText(QString)));


QTextDocument *document=ui->textEdit->document();//获取文档对象
QTextFrame *rootFrame=document->rootFrame();//获取根框架
QTextFrameFormat format;//创建框架格式
format.setBorderBrush(Qt::red);//边界颜色
format.setBorder(3);//边界宽度
rootFrame->setFrameFormat(format);//框架使用格式，还可以使用setHeight()和setWidth()函数来固定框架的高度和宽度

//使用光标类对象，在根框架中再添加一个子框架
QTextFrameFormat frameFormat;
frameFormat.setBackground(Qt::lightGray);//设置背景颜色
frameFormat.setMargin(10);//设置边距
frameFormat.setPadding(5);//设置填衬
frameFormat.setBorder(2);//
frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Dotted);//设置边框样式
QTextCursor cursor=ui->textEdit->textCursor();//获取光标
cursor.insertFrame(frameFormat);//在光标处插入框架

QAction *action_textFrame=new QAction(tr("框架"),this);
connect(action_textFrame,&QAction::triggered,this,&MainWindow::showTextFrame);
ui->mainToolBar->addAction(action_textFrame);//在工具栏添加动作


QAction *action_textBlock=new QAction(tr("文本块"),this);
connect(action_textBlock,&QAction::triggered,this,&MainWindow::showTextBlock);
ui->mainToolBar->addAction(action_textBlock);


//设置字体格式
QAction *action_font=new QAction(tr("字体"),this);
action_font->setCheckable(true);//设置动作可以被选中
connect(action_font,&QAction::toggled,this,&MainWindow::setTextFont);
ui->mainToolBar->addAction(action_font);


QAction *action_textTable=new QAction(tr("表格"),this);
QAction *action_textList=new QAction(tr("列表"),this);
QAction *action_textImage=new QAction(tr("图片"),this);
connect(action_textTable,&QAction::triggered,this,&MainWindow::insertTable);
connect(action_textList,&QAction::triggered,this,&MainWindow::insertList);
connect(action_textImage,&QAction::triggered,this,&MainWindow::insertImage);
ui->mainToolBar->addAction(action_textTable);
ui->mainToolBar->addAction(action_textList);
ui->mainToolBar->addAction(action_textImage);

//查找操作
QAction *action_textFind=new QAction(tr("查找"),this);
connect(action_textFind,&QAction::triggered,this,&MainWindow::textFind);
ui->mainToolBar->addAction(action_textFind);

findDialog=new QDialog(this);//创建对话框
lineEdit=new QLineEdit(findDialog);//创建行编辑器
QPushButton *btn=new QPushButton(findDialog);//创建按钮
btn->setText(tr("查找下一个"));
connect(btn,&QPushButton::clicked,this,&MainWindow::findNext);
QVBoxLayout *layout=new QVBoxLayout;//创建垂直布局管理器
layout->addWidget(lineEdit);//添加部件
layout->addWidget(btn);
findDialog->setLayout(layout);//在对话框中使用布局管理器

highlighter=new MySyntaxHighlighter(ui->textEdit->document());

ui->textEdit->append(tr("<h1><font color=green>使用HTML</font></h1>"));//在富文本处理中还提供了对HTML自己的支持
//可以在QLabel或者QTextEdit添加文本时使用HTML标签或者CSS属性

ui->textEdit->setAcceptDrops(false);
setAcceptDrops(true);
QLabel *label=new QLabel(this);
QPixmap pix("");
label->setPixmap(pix);//添加图片
label->resize(pix.size());//设置标签大小为图片大小
label->move(100,100);
label->setAttribute(Qt::WA_DeleteOnClose);//当窗口关闭时销毁图片


//打印
QAction *action_print=new QAction(tr("打印"),this);
QAction *action_printPreview=new QAction(tr("打印预览"),this);
QAction *action_pdf=new QAction(tr("生成pdf"),this);
connect(action_print,SIGNAL(triggered()),this,SLOT(doPrint()));
connect(action_printPreview,SIGNAL(triggered()),this,SLOT(doPrintPreview()));
connect(action_pdf,SIGNAL(triggered()),this,SLOT(createPdf()));
ui->mainToolBar->addAction(action_print);
ui->mainToolBar->addAction(action_printPreview);
ui->mainToolBar->addAction(action_pdf);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//添加完图片一定要先保存Ctrl+S，否则下面使用图片时将看不到图片

void MainWindow::on_action_New_triggered()//新建菜单
{
    //新建文本编辑器部件
    QTextEdit *edit=new QTextEdit(this);
    //使用QMdiArea类的addSubWindow()函数创建子窗口，以文本编辑器为中心部件
    QMdiSubWindow *child=ui->mdiArea->addSubWindow(edit);
    child->setWindowTitle(tr("多文档编辑器子窗口"));
    child->show();
}

void MainWindow::on_action_Dock_triggered()//显示工具箱
{
    ui->dockWidget->show();
}

void MainWindow::setText(const QString &string)//插入文本
{
    ui->textEdit->setText(string);//将获取的文本添加到编辑器中
}

void MainWindow::showTextFrame()//遍历框架
{
    QTextDocument *document=ui->textEdit->document();
    QTextFrame *frame=document->rootFrame();
    QTextFrame::iterator it; //建立QTextFrame类的迭代器
    for(it=frame->begin();!(it.atEnd());++it)
    {
        QTextFrame *childFrame=it.currentFrame();//获取当前框架的指针
        QTextBlock childBlock=it.currentBlock();//获取当前文本块
        if(childFrame)
            qDebug()<<"frame";
            else if(childBlock.isValid())
                qDebug()<<"block:"<<childBlock.text();


    }
}

void MainWindow::showTextBlock()//遍历文本块
{
    QTextDocument *document=ui->textEdit->document();
    QTextBlock block=document->firstBlock();//获取文档的第一个文本块
    for(int i=0;i<document->blockCount();i++)
    {
        qDebug()<<tr("文本块%1,文本块首行行号为:%2,长度为:%3,内容为").arg(i).arg(block.firstLineNumber()).arg(block.length())
               <<block.text();
        block=block.next();//获取下一个文本块

    }
}

void MainWindow::setTextFont(bool checked)//设置字体格式
{
    if(checked)//如果处于选中状态
    {
        QTextCursor cursor=ui->textEdit->textCursor();
        QTextBlockFormat blockFormat;//文本块格式
        blockFormat.setAlignment(Qt::AlignCenter);//水平居中
        cursor.insertBlock(blockFormat);//使用文本块格式
        QTextCharFormat charFormat;//字符格式
        charFormat.setBackground(Qt::lightGray);//背景色
        charFormat.setForeground(Qt::blue);//字体颜色
        //使用宋体，12号，加粗，倾斜
        charFormat.setFont(QFont(tr("宋体"),12,QFont::Bold,true));
        charFormat.setFontUnderline(true);//使用下划线
 cursor.setCharFormat(charFormat);//使用字符格式
 cursor.insertText(tr("测试字体"));//插入文本
    }
    else{/*恢复默认的字体格式*/}//如果处于非选中状态，可以进行其他操作
}

void MainWindow::insertTable()//插入表格
{
    QTextCursor cursor=ui->textEdit->textCursor();
    QTextTableFormat format;//表格格式
    format.setCellSpacing(2);//表格外边白
    format.setCellPadding(10);//表格内边白
    cursor.insertTable(2,2,format);//插入2行2列表格

}

void MainWindow::insertList()//插入列表
{
    QTextListFormat format;//列表格式
    format.setStyle(QTextListFormat::ListDecimal);//数字编号
    ui->textEdit->textCursor().insertList(format);

}

void MainWindow::insertImage()//插入图片
{
    QTextImageFormat format;//图片格式
    format.setName("E:/Qt(C++)/mymainwindow/images/aa.jpg");//图片路径
            ui->textEdit->textCursor().insertImage(format);
}
void MainWindow::textFind()//查找操作
{

    findDialog->show();
}
void MainWindow::findNext()//查找下一个
{
    QString string=lineEdit->text();
    //使用查找函数查找指定字符串，查找方式为向后查找,更多的查找功能可以使用QTextDocument类的find()函数，其中还可以使用正则表达式
    bool isfind=ui->textEdit->find(string,QTextDocument::FindBackward);
    if(isfind)//如果查找成功，输出字符串所在行和列的编号
    {
        qDebug()<<tr("行号:%1列号:%2")
                  .arg(ui->textEdit->textCursor().blockNumber())
                  .arg(ui->textEdit->textCursor().columnNumber());

    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)//拖动进入事件
{
    if(event->mimeData()->hasUrls())//数据中是否包含URL
        event->acceptProposedAction();//如果是则接收动作
    /*
    else if(event->mimeData()->hasFormat("myimage/png")){
        event->setDropAction(Qt::MoveAction);
        event->accept();

    }
    */
else{
        event->ignore();
    }

}
/*
void MainWindow::dragMoveEvent(QDragMoveEvent *event)//拖动事件
{
    if(event->mimeData()->hasFormat("myimage/png")){
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }else{
        event->ignore();
    }
}
*/

void MainWindow::dropEvent(QDropEvent *event)//放下事件
{
    const QMimeData *mimeData=event->mimeData();//获取MIME数据
    if(mimeData->hasUrls())//如果数据中包含URL
        {
        QList<QUrl>urlList=mimeData->urls();//获取URL列表
        //将其中第一个URL表示为本地文件路径
        QString fileName=urlList.at(0).toLocalFile();
        if(!fileName.isEmpty())//如果文件路径不为空
            {
            QFile file(fileName);//建立QFile对象并且以只读方式打开该文件
            if(!file.open(QIODevice::ReadOnly)) return;
            QTextStream in(&file);//建立文本流对象
            ui->textEdit->setText(in.readAll());//将文件中所有内容读入编辑器
        }
    }
    /*
    else if(event->mimeData()->hasFormat("myimage/png"))
    {
        QByteArray itemData=event->mimeData()->data("myimage/png");
        QDataStream dataStream(&itemData,QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        //使用数据流将字节数组中的数据读入到QPixmap和QPoint变量中
        dataStream>>pixmap>>offset;
        //新建标签，为其添加图片，并根据图片大小设置标签的大小
        QLabel *newLabel=new QLabel(this);
        newLabel->setPixmap(pixmap);
        newLabel->resize(pixmap.size());
        //让图片移动到放下的位置，不设置的话，图片会默认显示在（0,0）点即窗口左上角
        newLabel->move(event->pos()-offset);
        newLabel->show();
        newLabel->setAttribute(Qt::WA_DeleteOnClose);
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }else{
        event->ignore();
    }
    */
}
/*
void MainWindow::mousePressEvent(QMouseEvent *event)//鼠标按下事件
{
    //第一步：获取图片
    //将鼠标指针所在位置的部件强制转换为QLabel类型
    QLabel *child=static_cast<QLabel*>(childAt(event->pos()));
    if(!child->inherits("QLabel"))return;//如果部件不是QLabel则直接返回
    QPixmap pixmap=*child->pixmap();//获取QLabel中的图片
    //第2步：自定义MIME类型
    QByteArray itemData;//创建字节数组
    QDataStream dataStream(&itemData,QIODevice::WriteOnly);//创建数据流
    //将图片信息，位值信息输入到字节数组中
    dataStream<<pixmap<<QPoint(event->pos()-child->pos());
    //第3步：将数据放入QMimeData中
    QMimeData *mimeData=new QMimeData;//创建QMimeData用来存放要移动的数据
    //将字节数组放入QMimeData中，这里的MIME类型是我们自己定义的
    mimeData->setData("myimage/png",itemData);
    //第4步：将QMimeData数据放入QDrag中
    QDrag *drag=new QDrag(this);//创建QDrag,它用来移动数据
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);//在移动过程中显示图片，若不设置则设置默认显示一个小矩形
    drag->setHotSpot(event->pos()-child->pos());//拖动时鼠标指针的位置不变
    //第5步：给原图片添加阴影
    QPixmap tempPixmap=pixmap;//使原图片添加阴影
    QPainter painter;//创建QPainter，用来绘制QPixmap
    painter.begin(&tempPixmap);
    //在图片的外接矩形中添加一层透明的淡黑色形成阴影效果
    painter.fillRect(pixmap.rect(),QColor(127,127,127,127));
    painter.end();
    child->setPixmap(tempPixmap);//在移动图片过程中，让原图片添加一层黑色阴影
    //第6步：执行拖放操作
    //设置拖放可以是移动和复制操作，默认是复制操作
    if(drag->exec(Qt::CopyAction|Qt::MoveAction,Qt::CopyAction)==Qt::MoveAction)
        child->close();//如果是移动操作，那么拖放完后关闭原标签
    else{
        child->show();//如果是复制操作，那么拖放完成后显示标签
        child->setPixmap(pixmap);//显示原图片，不在使用阴影

    }

}
*/

void MainWindow::doPrint()//打印
{
    QPrinter printer;//创建打印机对象
    QPrintDialog dlg(&printer,this);//创建打印对话框
    //如果编辑器中有选中区域，则打印选中区域
    if(ui->textEdit->textCursor().hasSelection())
        dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if(dlg.exec()==QDialog::Accepted)//如果在对话框中按下了打印按钮
    {
        ui->textEdit->print(&printer);//则执行打印操作
    }
}

void MainWindow::doPrintPreview()//打印预览
{
    QPrinter printer;
    QPrintPreviewDialog preview(&printer,this);//创建打印预览对话框
    //当要生成预览页面时，发射paintRequested()信号
    connect(&preview,&QPrintPreviewDialog::paintRequested,this,&MainWindow::printPreview);
    preview.exec();
}

void MainWindow::printPreview(QPrinter *printer)
{
    ui->textEdit->print(printer);
}
void MainWindow::createPdf()//生成PDF文件
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("导出PDF文件"),QString(),"*.pdf");
    if(!fileName.isEmpty())
    {
        if(QFileInfo(fileName).suffix().isEmpty())
        fileName.append(".pdf");//如果文件后缀为空，则默认使用.pdf
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);//指定输出格式为.pdf
        printer.setOutputFileName(fileName);
        ui->textEdit->print(&printer);
    }
}
