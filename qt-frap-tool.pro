#-------------------------------------------------
#
# Project created by QtCreator 2012-06-10T20:54:39
#
#-------------------------------------------------

QT       += core gui

TARGET = qt-frap-tool
TEMPLATE = app
LIBS += -L/usr/local/lib -lfraptool-1.0 -lplplotcxxd -lltdl -ldl -lcsirocsa -lqhull -lqsastime -lfreetype -L/usr/X11R6/lib -lpthread -lX11 -ltiff -lboost_thread-mt -lgsl -lgslcblas
INCLUDEPATH += /usr/local/include/fraptool-1.0


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
