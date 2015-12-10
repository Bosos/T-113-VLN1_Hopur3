QT += core
QT += sql
QT += gui
QT += widgets

TARGET = ComputerScientistsW3
CONFIG += console
CONFIG += app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    Console.cpp \
    DataManager.cpp \
    Scientist.cpp \
    Computer.cpp \
    TypeOfComputer.cpp \
    SortBy.cpp \
    MainWindow.cpp \
    SearchCriteria.cpp

HEADERS += \
    Console.h \
    DataManager.h \
    Scientist.h \
    SortBy.h \
    Computer.h \
    TypeOfComputer.h \
    MainWindow.h \
    SearchCriteria.h

FORMS += \
    mainwindow.ui
