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
        MainWindow/mainwindow.cpp \
    BasicModeWindow/basicmodewindow.cpp \
    RelaxedModeWindow/relaxedmodewindow.cpp \
    LevelModeWindow/levelmodewindow.cpp \
    Model/game.cpp \
    Dao/scoredao.cpp \
    HelpDialog/helpdialog.cpp \
    Model/DrawLineLayer.cpp

HEADERS  += MainWindow/mainwindow.h \
    BasicModeWindow/basicmodewindow.h \
    RelaxedModeWindow/relaxedmodewindow.h \
    LevelModeWindow/levelmodewindow.h \
    Model/mapbutton.h \
    Model/game.h \
    Dao/scoredao.h \
    HelpDialog/helpdialog.h \
    Model/DrawLineLayer.h

FORMS    += mainwindow.ui \
    basicmodewindow.ui \
    relaxedmodewindow.ui \
    levelmodewindow.ui

RESOURCES += \
    res.qrc

DISTFILES +=
