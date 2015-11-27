QT += core
QT -= gui

TARGET = ComputerScientistsW3
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    datamanager.cpp \
    scientist.cpp \
    console.cpp

HEADERS += \
    datamanager.h \
    scientist.h \
    console.h

