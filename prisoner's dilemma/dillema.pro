#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T11:58:32
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = dillema
CONFIG   += console
CONFIG   -= app_bundle

CONFIG += debug

TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    evil_strategy.cpp \
    Factory.cpp \
    game.cpp \
    gentle_strategy.cpp \
    matrix.cpp \
    prisoner.cpp \
    random_strategy.cpp \
    strategy.cpp \
    main.cpp \
    repetition_strategy.cpp \
    opposite_strategy.cpp \
    tit_for_tat.cpp \
    input_reading.cpp \
    game_modes.cpp

HEADERS += \
    evil_strategy.h \
    Factory.h \
    game.h \
    gentle_strategy.h \
    matrix.h \
    prisoner.h \
    random_strategy.h \
    strategy.h \
    repetition_strategy.h \
    opposite_strategy.h \
    tit_for_tat.h \
    input_reading.h \
    game_modes.h \
    variables.h

DISTFILES += \
    strategies.txt \
    Game_matrix.txt
