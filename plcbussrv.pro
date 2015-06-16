QT = core serialport network

CONFIG += console
CONFIG -= app_bundle

TARGET = plcbussrv
TEMPLATE = app

target.path = /usr/bin/
INSTALLS += target

HEADERS += log.h serial.h tcpserv.h
SOURCES += main.cpp serial.cpp tcpserv.cpp
