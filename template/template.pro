QT += core
QT -= gui

TARGET = template
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
TEMPLATE = app

SOURCES += main.cpp \
    graph.cpp \
    mgraph.cpp \
    lgraph.cpp


INCLUDEPATH += /home/artem/OOP/template/boost_1_59_0/

LIBS += -L/home/artem/OOP/template/boost_1_59_0/stage/lib

HEADERS += \
    graph.h \
    algorithms.h \
    mgraph.h \
    lgraph.h
