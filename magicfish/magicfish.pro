#-------------------------------------------------
#
# Project created by QtCreator 2018-7-14T10:23:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = magicfish
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += qt warn_off

SOURCES     += main.cpp
SOURCES     += magicfish.cpp
SOURCES     += magicpool.cpp

HEADERS     += magicfish.h
HEADERS     += magicpool.h
