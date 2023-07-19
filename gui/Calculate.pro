######################################################################
# Automatically generated by qmake (3.1) Sat Jul 1 17:37:09 2023
######################################################################

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17 qtc_runnable


TEMPLATE = app
TARGET = Calculate
INCLUDEPATH += .

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x060000 # disables all APIs deprecated in Qt 6.0.0 and earlier

# Input
HEADERS += mainwindow.h \
    credit.h \
    credit_calc.h \
    deposit.h \
    parser.h \
    qcustomplot.h \
    result_credit.h \
    result_deposit.h \
    stack.h
FORMS += mainwindow.ui \
    credit.ui \
    deposit.ui \
    result_credit.ui \
    result_deposit.ui
SOURCES += main.cpp mainwindow.cpp \
    credit.cpp \
    credit_calc.c \
    deposit.cpp \
    parser.c \
    qcustomplot.cpp \
    result_credit.cpp \
    result_deposit.cpp \
    stack.c