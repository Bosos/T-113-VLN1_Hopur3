QT += core
QT -= gui

TARGET = ComputerScientistsW3
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Console.cpp \
    DataManager.cpp \
    Scientist.cpp

HEADERS += \
    Console.h \
    DataManager.h \
    Scientist.h \
    SortBy.h

