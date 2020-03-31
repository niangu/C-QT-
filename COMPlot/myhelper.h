#ifndef MYHELPER_H
#define MYHELPER_H

#include <QtCore>
#include <QtGui>
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
#include <QtWidgets>
#endif

class myHelper: public QObject
{

public:    

    //窗体居中显示
    static void FormInCenter(QWidget *frm) {
        int frmX = frm->width();
        int frmY = frm->height();
        QDesktopWidget w;
        int deskWidth = w.availableGeometry().width();
        int deskHeight = w.availableGeometry().height();
        QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
        frm->move(movePoint);
    }

    //设置编码为UTF8
    static void SetUTF8Code() {
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForLocale(codec);
        QTextCodec::setCodecForCStrings(codec);
        QTextCodec::setCodecForTr(codec);
#endif
    }

    //延时
    static void Sleep(int sec) {
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while ( QTime::currentTime() < dieTime ) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }

    //计算校验码
    static uchar GetCheckCode(uchar data[], uchar len) {
        uchar temp = 0;
        for (uchar i = 0; i < len; i++) {
            temp += data[i];
        }
        return temp % 256;
    }

    //将溢出的char转为正确的uchar
    static uchar GetUChar(char data) {
        uchar temp;
        if (data > 127) {
            temp = data + 256;
        } else {
            temp = data;
        }
        return temp;
    }

    //16进制字符串转字节数组
    static QByteArray HexStrToByteArray(QString str) {
        QByteArray senddata;
        int hexdata, lowhexdata;
        int hexdatalen = 0;
        int len = str.length();
        senddata.resize(len / 2);
        char lstr, hstr;
        for(int i = 0; i < len; ) {
            hstr = str[i].toLatin1();
            if(hstr == ' ') {
                i++;
                continue;
            }
            i++;
            if(i >= len) {
                break;
            }
            lstr = str[i].toLatin1();
            hexdata = ConvertHexChar(hstr);
            lowhexdata = ConvertHexChar(lstr);
            if((hexdata == 16) || (lowhexdata == 16)) {
                break;
            } else {
                hexdata = hexdata * 16 + lowhexdata;
            }
            i++;
            senddata[hexdatalen] = (char)hexdata;
            hexdatalen++;
        }
        senddata.resize(hexdatalen);
        return senddata;
    }

    static char ConvertHexChar(char ch) {
        if((ch >= '0') && (ch <= '9')) {
            return ch - 0x30;
        } else if((ch >= 'A') && (ch <= 'F')) {
            return ch - 'A' + 10;
        } else if((ch >= 'a') && (ch <= 'f')) {
            return ch - 'a' + 10;
        } else {
            return (-1);
        }
    }

    //字节数组转16进制字符串
    static QString ByteArrayToHexStr(QByteArray data) {
        QString temp = "";
        QString hex = data.toHex();
        for (int i = 0; i < hex.length(); i = i + 2) {
            temp += hex.mid(i, 2) + " ";
        }
        return temp.trimmed().toUpper();
    }

    //16进制字符串转10进制
    static int StrHexToDecimal(QString strHex) {
        bool ok;
        return strHex.toInt(&ok, 16);
    }

    //10进制字符串转10进制
    static int StrDecimalToDecimal(QString strDecimal) {
        bool ok;
        return strDecimal.toInt(&ok, 10);
    }

    //2进制字符串转10进制
    static int StrBinToDecimal(QString strBin) {
        bool ok;
        return strBin.toInt(&ok, 2);
    }

    //16进制字符串转2进制字符串
    static QString StrHexToStrBin(QString strHex) {
        uchar decimal = StrHexToDecimal(strHex);
        QString bin = QString::number(decimal, 2);

        uchar len = bin.length();
        if (len < 8) {
            for (int i = 0; i < 8 - len; i++) {
                bin = "0" + bin;
            }
        }

        return bin;
    }

    //10进制转为2进制字符串一个字节
    static QString DecimalToStrBin1(int decimal) {
        QString bin = QString::number(decimal, 2);

        uchar len = bin.length();
        if (len <= 8) {
            for (int i = 0; i < 8 - len; i++) {
                bin = "0" + bin;
            }
        }

        return bin;
    }

    //10进制转为2进制字符串两个字节
    static QString DecimalToStrBin2(int decimal) {
        QString bin = QString::number(decimal, 2);

        uchar len = bin.length();
        if (len <= 16) {
            for (int i = 0; i < 16 - len; i++) {
                bin = "0" + bin;
            }
        }

        return bin;
    }

    //10进制转为16进制字符串补全零
    static QString DecimalToStrHex(int decimal) {
        QString temp = QString::number(decimal, 16);
        if (temp.length() == 1) {
            temp = "0" + temp;
        }
        return temp;
    }

};

#endif // MYHELPER_H
