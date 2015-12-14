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
    DataManager.cpp \
    Scientist.cpp \
    Computer.cpp \
    TypeOfComputer.cpp \
    SortBy.cpp \
    mainwindow.cpp \
    SearchCriteria.cpp \
    Service.cpp

HEADERS += \
    DataManager.h \
    Scientist.h \
    SortBy.h \
    Computer.h \
    TypeOfComputer.h \
    SearchCriteria.h \
    Service.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
