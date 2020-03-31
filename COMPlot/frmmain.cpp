#include "frmmain.h"
#include "ui_frmmain.h"
#include "myhelper.h"

#define _TIME_ qPrintable (QTime::currentTime().toString("hh:mm:ss:zzz"))

frmMain::frmMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
    myHelper::FormInCenter(this);
    this->InitForm();
    this->InitPlot();
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::InitForm()
{
    this->showMaximized();
    MaxCount = 100;
    CurrentCount = 0;
    SleepTime = 100;
    ReceiveCount = 0;
    SendCount = 0;
    IsShow = true;
    IsHexSend = true;
    IsHexReceive = true;

    com = 0;
    QStringList comList;//串口号
    QStringList baudList;//波特率
    QStringList parityList;//校验位
    QStringList dataBitsList;//数据位
    QStringList stopBitsList;//停止位

#ifdef Q_OS_WIN32
    comList.clear();
    comList << "COM1" << "COM2" << "COM3" << "COM4" << "COM5" << "COM6" << "COM7" << "COM8";
#endif
#ifdef Q_OS_LINUX
#ifdef __arm__
    comList.clear();
    comList << "ttySAC0" << "ttySAC1" << "ttySAC2" << "ttySAC3";
#else
    comList.clear();
    comList << "ttyUSB0" << "ttyS0" << "ttyS1" << "ttyS2" << "ttyS3" << "ttyS4";
#endif
#endif

    ui->cboxPortName->addItems(comList);
    ui->cboxPortName->setCurrentIndex(0);

    baudList << "50" << "75" << "100" << "134" << "150" << "200" << "300"
             << "600" << "1200" << "1800" << "2400" << "4800" << "9600"
             << "14400" << "19200" << "38400" << "56000" << "57600"
             << "76800" << "115200" << "128000" << "256000";

    ui->cboxBaudRate->addItems(baudList);
    ui->cboxBaudRate->setCurrentIndex(12);

    parityList << "无" << "奇" << "偶";

#ifdef Q_OS_WIN//如果是windows系统
    parityList << "标志";
#endif

    parityList << "空格";

    ui->cboxParity->addItems(parityList);
    ui->cboxParity->setCurrentIndex(0);

    dataBitsList << "5" << "6" << "7" << "8";
    ui->cboxDataBit->addItems(dataBitsList);
    ui->cboxDataBit->setCurrentIndex(3);

    stopBitsList << "1";

#ifdef Q_OS_WIN//如果是windows系统
    stopBitsList << "1.5";
#endif

    stopBitsList << "2";

    ui->cboxStopBit->addItems(stopBitsList);
    ui->cboxStopBit->setCurrentIndex(0);

    for (int i = 0; i <= 500; i = i + 50) {
        ui->cboxSleepTime->addItem(QString::number(i));
    }
    ui->cboxSleepTime->setCurrentIndex(2);

    ui->cboxInterval->addItem(QString::number(100));
    ui->cboxInterval->addItem(QString::number(200));
    ui->cboxInterval->addItem(QString::number(300));
    for (int i = 500; i <= 10000; i = i + 500) {
        ui->cboxInterval->addItem(QString::number(i));
    }
    ui->cboxInterval->setCurrentIndex(4);

    for (int i = 100; i <= 1000; i = i + 100) {
        ui->cboxMaxCount->addItem(QString::number(i));
    }

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(WriteData()));
    timer->start();

    QString fileName = QString("%1/%2").arg(qApp->applicationDirPath()).arg("ConfigData.txt");
    QFile file(fileName);
    if (!file.exists()) {
        return;
    }

    ui->txtSend->clear();
    file.open(QFile::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString line;

    do {
        line = in.readLine();
        if (line != "") {
            ui->txtSend->addItem(line);
        }
    } while(!line.isNull());

    file.close();
}

void frmMain::InitPlot()
{
    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(Qt::red));
    ui->plot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->plot->graph(0)->setAntialiasedFill(true);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::red, 1), QBrush(Qt::white), 9));

    ui->plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->plot->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->plot->xAxis->setAutoTickStep(false);
    ui->plot->xAxis->setTickStep(1);
    ui->plot->xAxis->setRange(0, 5, Qt::AlignRight);
    ui->plot->yAxis->setRange(0, 255);

    ui->plot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->plot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->plot->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->plot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->plot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->plot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->plot->xAxis->setTickLabelColor(Qt::white);
    ui->plot->yAxis->setTickLabelColor(Qt::white);

    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->plot->setBackground(plotGradient);

    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->plot->axisRect()->setBackground(axisRectGradient);

    ///ui->plot->axisRect()->setupFullAxesBox();
    ui->plot->replot();

    timerPlot = new QTimer(this);
    connect(timerPlot, SIGNAL(timeout()), this, SLOT(addPlot()));
}

void frmMain::Append(QString msg, bool isSend)
{
    if (!IsShow) {
        return;
    }

    if (CurrentCount >= MaxCount) {
        ui->txtMain->clear();
        CurrentCount = 0;
    }

    QString str = "接收";
    if (isSend) {
        str = "发送";
    }

    ui->txtMain->append(QString("%1:%2 时间:%3")
                        .arg(str)
                        .arg(msg)
                        .arg(_TIME_));
    CurrentCount++;
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
}

void frmMain::ReadData()
{
    if (com->bytesAvailable() <= 0) {
        return;
    }

    myHelper::Sleep(SleepTime);
    QByteArray buffer = com->readAll();
    if (buffer.length() == 0) {
        return;
    }

    //以下增加部分为将接收数据曲线显示
    QVector<double> keys;
    QVector<double> values;
    double key;
    for (int i = 0; i < buffer.length(); i++) {
        key = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
        keys.append(key);
        values.append(buffer[i]);
    }
    ui->plot->graph(0)->addData(keys, values);
    ui->plot->graph(0)->removeDataBefore(key - 5);
    ui->plot->xAxis->setRange(key, 5, Qt::AlignRight);
    ui->plot->replot();

    if (IsHexReceive) {
        Append(myHelper::ByteArrayToHexStr(buffer), false);
    } else {
        Append(QString(buffer), false);
    }

    ReceiveCount = ReceiveCount + buffer.size();
    ui->btnReceiveCount->setText(QString("接收: %1 字节").arg(ReceiveCount));
}

void frmMain::WriteData()
{
    if (!ui->ckIsAutoSend->isChecked()) {
        return;
    }

    on_btnSend_clicked();
}

void frmMain::on_btnOpen_clicked()
{
    if (ui->btnOpen->text() == "打开串口") {
        QString portName = ui->cboxPortName->currentText();
        com = new QextSerialPort(portName, QextSerialPort::EventDriven, this);

        if (com->open(QIODevice::ReadWrite)) {
            //清空缓冲区
            com->flush();
            //设置波特率
            com->setBaudRate((BaudRateType)ui->cboxBaudRate->currentText().toInt());
            //设置数据位
            com->setDataBits((DataBitsType)ui->cboxDataBit->currentText().toInt());
            //设置校验位
            com->setParity((ParityType)ui->cboxParity->currentIndex());
            //设置停止位
            com->setStopBits((StopBitsType)ui->cboxStopBit->currentIndex());
            com->setFlowControl(FLOW_OFF);
            com->setTimeout(10);
            connect(com, SIGNAL(readyRead()), this, SLOT(ReadData()), Qt::DirectConnection);
            ui->btnOpen->setText("关闭串口");
        }
    } else {
        disconnect(com, SIGNAL(readyRead()), this, SLOT(ReadData()));
        myHelper::Sleep(100);
        com->flush();
        com->close();
        com = 0;
        ui->btnOpen->setText("打开串口");
        on_btnClearCount_clicked();
        on_btnClearAll_clicked();
    }
}

void frmMain::on_btnClearCount_clicked()
{
    CurrentCount = 0;
    SendCount = 0;
    ReceiveCount = 0;
    ui->btnSendCount->setText("发送: 0 字节");
    ui->btnReceiveCount->setText("接收: 0 字节");
}

void frmMain::on_btnStopShow_clicked()
{
    if (ui->btnStopShow->text() == "停止显示") {
        IsShow = false;
        ui->btnStopShow->setText("开始显示");
    } else {
        IsShow = true;
        ui->btnStopShow->setText("停止显示");
    }
}

void frmMain::on_btnClearAll_clicked()
{
    ui->txtMain->clear();
}

void frmMain::on_btnSave_clicked()
{
    QString data = ui->txtMain->toPlainText();
    if (data == "") {
        return;
    }

    QDateTime now = QDateTime::currentDateTime();
    QString name = now.toString("yyyyMMddHHmmss");
    QString fileName = QString("%1/%2.txt").arg(qApp->applicationDirPath()).arg(name);

    QFile file(fileName);
    file.open(QFile::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << data;
    file.close();
}

void frmMain::on_ckHexSend_stateChanged(int arg1)
{
    IsHexSend = (arg1 == 0 ? false : true);
}

void frmMain::on_ckHexReceive_stateChanged(int arg1)
{
    IsHexReceive = (arg1 == 0 ? false : true);
}

void frmMain::on_btnSend_clicked()
{
    if (com == 0 || !com->isOpen()) {
        return;
    }

    QString data = ui->txtSend->currentText();
    if (data == "") {
        ui->txtSend->setFocus();
        return;
    }

    QByteArray outData = data.toUtf8();
    int size = outData.size();

    if (IsHexSend) {
        outData = myHelper::HexStrToByteArray(data);
        size = outData.size();
        com->write(outData);
    } else {
        size = outData.size();
        com->write(outData);
    }

    Append(data, true);
    SendCount = SendCount + size;
    ui->btnSendCount->setText(QString("发送: %1 字节").arg(SendCount));
}

void frmMain::on_cboxInterval_activated(const QString &arg1)
{
    timer->setInterval(arg1.toInt());
}

void frmMain::on_cboxSleepTime_activated(const QString &arg1)
{
    SleepTime = arg1.toInt();
}

void frmMain::on_cboxMaxCount_activated(const QString &arg1)
{
    MaxCount = arg1.toInt();
}

void frmMain::on_btnPlot_clicked()
{
    if (ui->btnPlot->text() == "开始模拟曲线") {
        connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->xAxis2, SLOT(setRange(QCPRange)));
        connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->yAxis2, SLOT(setRange(QCPRange)));
        timerPlot->start(100);
        ui->btnPlot->setText("停止模拟曲线");
    } else {
        disconnect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->xAxis2, SLOT(setRange(QCPRange)));
        disconnect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->yAxis2, SLOT(setRange(QCPRange)));
        timerPlot->stop();
        ui->btnPlot->setText("开始模拟曲线");
        ui->plot->yAxis->setRange(0, 255);
        ui->plot->replot();
    }
}

void frmMain::addPlot()
{    
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
    ui->plot->graph(0)->addData(key, qSin(key));
    ui->plot->graph(0)->removeDataBefore(key - 5);
    ui->plot->xAxis->setRange(key, 5, Qt::AlignRight);
    ui->plot->graph(0)->rescaleValueAxis();
    ui->plot->replot();
}
