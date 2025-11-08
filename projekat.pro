#-------------------------------------------------
#
# Project created by QtCreator 2025-05-17T15:25:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

TARGET = projekat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    dialogbrisanjeid.cpp \
    dialoginfo.cpp \
    dialoghelp.cpp \
    ganttdialog.cpp

HEADERS  += mainwindow.h \
    database.h \
    dialogbrisanjeid.h \
    dialoginfo.h \
    dialoghelp.h \
    ganttdialog.h

FORMS    += mainwindow.ui \
    dialogbrisanjeid.ui \
    dialoginfo.ui \
    dialoghelp.ui \
    ganttdialog.ui
