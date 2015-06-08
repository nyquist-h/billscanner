#-------------------------------------------------
#
# Project created by QtCreator 2015-01-29T20:21:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = gnucache-bill-importer
TEMPLATE = app


SOURCES += main.cpp\
           mainWindow.cpp

HEADERS  += mainWindow.h

FORMS    += mainWindow.ui

INCLUDEPATH += /home/nyquist/projects/gnucach-bill-importer/src/
LIBS        += -L/home/nyquist/projects/gnucash-bill-importer/build/debug -lgnucache-bill-importer
#TODO change indluce and lib path
