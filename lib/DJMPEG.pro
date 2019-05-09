CONFIG += console c++17
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++17

TEMPLATE = subdirs
 
  SUBDIRS = src/DJMPEGlib src/testapp

  # build the project sequentially as listed in SUBDIRS !
  CONFIG += ordered
