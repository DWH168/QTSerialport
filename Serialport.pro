#-------------------------------------------------
#
# Project created by QtCreator 2020-04-22T17:49:19
#
#-------------------------------------------------

QT       += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Serialport
TEMPLATE = app


SOURCES += main.cpp\
        serialport.cpp

HEADERS  += serialport.h

FORMS    += serialport.ui
