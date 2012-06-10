#-------------------------------------------------
#
# Project created by QtCreator 2012-06-10T20:54:39
#
#-------------------------------------------------

QT       += core gui

TARGET = qt-frap-tool
TEMPLATE = app
LIBS += -lgsl -lgslcblas
INCLUDEPATH += /home/jon/Programming/C/frap-tool/include


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
