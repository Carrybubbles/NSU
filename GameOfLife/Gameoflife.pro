#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T23:44:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gameoflife
TEMPLATE = app

CONFIG += c++11 c++1y -g

SOURCES += main.cpp\
                            controller.cpp \
                            lifemodel.cpp \
                            field.cpp \
                            view.cpp \
    parser.cpp

HEADERS  +=  \
    controller.h \
    lifemodel.h \
    field.h \
    view.h \
    variables.h \
    parser.h

FORMS    += mainwindow.ui
