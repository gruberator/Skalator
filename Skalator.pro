#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T06:06:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Skalator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tune.cpp \
    scale.cpp \
    scaleslistmodel.cpp \
    fretboard.cpp \
    tunelistviewmodel.cpp \
    settingsmanager.cpp

HEADERS  += mainwindow.h \
    tune.h \
    scale.h \
    scaleslistmodel.h \
    fretboard.h \
    tunelistviewmodel.h \
    settingsmanager.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    LICENSE \
    README
