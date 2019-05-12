TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17 -std=c++1z

#QMAKE_LFLAGS += -m32
#QMAKE_CXXFLAGS += -m32

SOURCES += \
    testmpeg-main.cpp

HEADERS += ..\DJMPEGlib\include\DJMPEGlib.h \
    ../../../DJCommon/include/my_buf_view.hpp \
    ../../../DJCommon/include/my_logging.hpp \
    ../../../DJCommon/include/my_types.hpp \
    ../DJMPEGlib/include/DJMPEGlib.hpp

LIBS += -lstdc++fs
