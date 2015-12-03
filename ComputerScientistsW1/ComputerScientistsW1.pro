QT += core
QT -= gui

TARGET = ComputerScientistsW3
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    Console.cpp \
    DataManager.cpp \
    Scientist.cpp \
    CSVReader.cpp \
    CSVWriter.cpp \
    Computer.cpp

HEADERS += \
    Console.h \
    DataManager.h \
    Scientist.h \
    SortBy.h \
    CSVReader.h \
    CSVWriter.h \
    Computer.h

