CONFIG += console c++14
CONFIG -= app_bundle
CONFIG+= static
CONFIG += warn_on
QMAKE_CXXFLAGS_WARN_ON = -Wall -pedantic

win32:  INCLUDEPATH += C:/boost_1_63_0
unix:   INCLUDEPATH += /home/user/boost_1_63_0

TEMPLATE = app

QT += core

SOURCES += \
    sdata.cpp \
    inversemat.cpp \
    sgfilter.cpp \
    main.cpp \
    mafilter.cpp

HEADERS += \
    sgf.h

