#-------------------------------------------------
#
# Project created by QtCreator 2013-07-22T16:45:50
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       +=core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyselfQQ
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    drawer.cpp \
    server.cpp \
    client.cpp \
    md5_check.cpp \
    login.cpp \
    admin.cpp \
    qtrsa.cpp

HEADERS  += widget.h \
    drawer.h \
    server.h \
    client.h \
    md5_check.h \
    login.h \
    admin.h \
    rsa.h \
    qtrsa.h

FORMS    += widget.ui \
    server.ui \
    client.ui \
    md5_check.ui \
    login.ui \
    admin.ui \
    qtrsa.ui

RESOURCES += \
    images.qrc
