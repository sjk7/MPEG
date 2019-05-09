TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17

SOURCES += \
    testmpeg-main.cpp

HEADERS += ..\DJMPEGlib\include\DJMPEGlib.h

LIBS += -lstdc++fs
