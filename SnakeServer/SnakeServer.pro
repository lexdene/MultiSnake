TEMPLATE = app
QT       += core network
QT       -= gui

include(../dgpapi.pri)

TARGET = SnakeServer
CONFIG   += console
CONFIG   -= app_bundle
INCLUDEPATH += ../SnakeCommon/

HEADERS += main/jargumentanalyse.h \
    network/jsnakeserver.h \
    ../SnakeCommon/jsnakeglobal.h \
    ../SnakeCommon/jsnakegame.h \
    ../SnakeCommon/jsnake.h \
    service/juserlistmanager.h \
    service/jroommanager.h \
    service/jsnakegameonserver.h \
    network/jsnakeserverprocessor.h \
    network/jsnakeserverdisconnectedprocessor.h \
    network/jsnakeserverroomsocketmanager.h
SOURCES += main/jargumentanalyse.cpp \
    main/main.cpp \
    network/jsnakeserver.cpp \
    ../SnakeCommon/jsnakegame.cpp \
    ../SnakeCommon/jsnake.cpp \
    service/juserlistmanager.cpp \
    service/jroommanager.cpp \
    ../SnakeCommon/jsnakestream.cpp \
    service/jsnakegameonserver.cpp \
    network/jsnakeserverprocessor.cpp \
    network/jsnakeserverdisconnectedprocessor.cpp \
    network/jsnakeserverroomsocketmanager.cpp
