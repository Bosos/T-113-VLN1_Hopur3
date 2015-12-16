QT += core
QT += sql
QT += gui
QT += widgets

TARGET = "The Computer Scientist Databasease"
DEPLOYMENT.display_name = The Computer Scientist Databasease
CONFIG += console
CONFIG += app_bundle
CONFIG += c++11
RC_FILE = myapp.rc

TEMPLATE = app

SOURCES += main.cpp \
    DataManager.cpp \
    Scientist.cpp \
    Computer.cpp \
    mainwindow.cpp \
    SearchCriteria.cpp \
    Service.cpp

HEADERS += \
    DataManager.h \
    Scientist.h \
    Computer.h \
    SearchCriteria.h \
    Service.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
