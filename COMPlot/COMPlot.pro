#-------------------------------------------------
#
# Project created by QtCreator 2014-08-15T14:34:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = COMPlot
TEMPLATE = app

win32 { SOURCES += serialportapi/qextserialport_win.cpp }
unix { SOURCES += serialportapi/qextserialport_unix.cpp }

SOURCES += main.cpp\
    serialportapi/qextserialport.cpp \
    qcustomplot.cpp \
    frmmain.cpp

HEADERS  += \
    serialportapi/qextserialport.h \
    serialportapi/qextserialport_global.h \
    serialportapi/qextserialport_p.h \
    qcustomplot.h \
    myhelper.h \
    frmmain.h

FORMS    += \     
    frmmain.ui

INCLUDEPATH += $$PWD

MOC_DIR         = temp/moc
RCC_DIR         = temp/rcc
UI_DIR          = temp/ui
OBJECTS_DIR     = temp/obj
DESTDIR         = bin
