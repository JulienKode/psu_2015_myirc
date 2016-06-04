#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T18:51:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Interface
TEMPLATE = app


SOURCES += main.cpp\
        interface.cpp \
    connection.cpp \
    ../client.c

HEADERS  += interface.h \
    connection.h \
    ../../../includes/irc.h

FORMS    += interface.ui \
    connection.ui
