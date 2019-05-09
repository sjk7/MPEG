TEMPLATE = lib
CONFIG += console c++17
CONFIG -= qt

#QMAKE_CXXFLAGS += -std=c++17

QMAKE_CXXFLAGS += -std=c++1z

HEADERS += \
    include/DJMPEGlib.hpp
