#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T17:03:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    basicmodewindow.cpp \
    relaxedmodewindow.cpp \
    levelmodewindow.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    basicmodewindow.h \
    relaxedmodewindow.h \
    levelmodewindow.h \
    game.h \
    mapbutton.h

FORMS    += mainwindow.ui \
    basicmodewindow.ui \
    relaxedmodewindow.ui \
    levelmodewindow.ui

RESOURCES += \
    res.qrc

DISTFILES +=
