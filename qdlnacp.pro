#-------------------------------------------------
#
# Project created by QtCreator 2013-02-02T23:37:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uPnP
TEMPLATE = app
CONFIG += debug warn_on qt threads link_pkgconfig
PKGCONFIG += libupnp

QMAKE_CXXFLAGS += -std=c++0x -g -DDEBUG -Iinclude

SOURCES += src/Config.cpp \
    src/Container.cpp \
    src/Device.cpp \
    src/DeviceList.cpp \
    src/Icon.cpp \
    src/Item.cpp \
    src/main.cpp\
    src/mainwindow.cpp \
    src/Service.cpp \
    src/TcpClient.cpp \
    src/Thread.cpp \
    src/UPnP_CP.cpp \
    src/UPnP_MediaServer.cpp \
    src/UPnP_MediaRenderer.cpp \
    src/xmltools.cpp \
    src/HttpClient.cpp \
    src/Log.cpp \
    src/UPnP.cpp

HEADERS  += include/mainwindow.h \
    include/Device.h \
    include/xmltools.h \
    include/Service.h \
    include/Uri.h \
    include/Container.h \
    include/Item.h \
    include/Config.h \
    include/UPnP_MediaServer.h \
    include/UPnP_MediaRenderer.h \
    include/UPnP_CP.h \
    include/Device.h \
    include/DeviceList.h \
    include/HttpClient.h \
    include/Icon.h \
    include/TcpClient.h \
    include/Thread.h \
    include/UPnP.h \
    include/Log.h

FORMS    += forms/mainwindow.ui

RESOURCES += \
    resorces.qrc
