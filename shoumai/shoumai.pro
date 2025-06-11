#-------------------------------------------------
#
# Project created by QtCreator 2025-06-08T22:18:56
#
#-------------------------------------------------

QT       += core gui widgets
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shoumai
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    phone.cpp \
    user.cpp \
    sale.cpp \
    account.cpp

HEADERS  += mainwindow.h \
    phone.h \
    user.h \
    sale.h \
    account.h

FORMS += \
    phone.ui \
    user.ui \
    sale.ui \
    account.ui
