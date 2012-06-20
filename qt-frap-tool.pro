#-------------------------------------------------
#
# Project created by QtCreator 2012-06-10T20:54:39
#
#-------------------------------------------------

QT       += core gui

TARGET = qt-frap-tool
TEMPLATE = app
LIBS += -L/usr/local/lib `pkg-config fraptool-1.0 --libs`
INCLUDEPATH += /usr/local/include/fraptool-1.0


SOURCES += main.cpp\
        mainwindow.cpp \
    frapmodel.cpp

HEADERS  += mainwindow.h \
    frapmodel.h

FORMS    += mainwindow.ui
