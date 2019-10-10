TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    methods.cpp \
    Testlib.cpp

HEADERS += \
    segment3d.h \
    line3d.h \
    vector3d.h \
    sphere3d.h \
    plane3d.h \
    Testlib.h
