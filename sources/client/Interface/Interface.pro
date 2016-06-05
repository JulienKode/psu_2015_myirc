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
    ../cmd.c \
    ../list.c \
    ../send_buff.c \
    ../cmd_2.c \
    smileylist.cpp

HEADERS  += interface.h \
    connection.h \
    ../../../includes/irc.h \
    smileylist.h

FORMS    += interface.ui \
    connection.ui \
    smileylist.ui

DISTFILES +=
