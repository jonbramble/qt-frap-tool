#-------------------------------------------------
#
# Project created by QtCreator 2012-06-10T20:54:39
#
#-------------------------------------------------

QT       += core gui

TARGET = qt-frap-tool
TEMPLATE = app

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += fraptool-1.0 plplotd-qt
}

INCLUDEPATH += /usr/local/include/fraptool-1.0


SOURCES += main.cpp\
        mainwindow.cpp \
    frapmodel.cpp \
    plplotwidget.cpp

HEADERS  += mainwindow.h \
    frapmodel.h \
    plplotwidget.h \
    qt.h

FORMS    += mainwindow.ui
