#-------------------------------------------------
#
# Project created by QtCreator 2013-12-16T16:37:12
#
#-------------------------------------------------

unix: QWT_ROOT = /usr/local/qwt-6.1.0
win32: QWT_ROOT = C:/Qt/Qwt-6.1.0
include ( $${QWT_ROOT}/features/qwt.prf )

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = solving-system-ode
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
