TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += warn_on

QMAKE_CXXFLAGS_RELEASE += -O2
QMAKE_CXXFLAGS += -Wall -Wextra -Wfloat-equal -Wundef -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wshadow -Wdiv-by-zero
QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]

SOURCES += \
    main.cpp \
    Testlib.cpp

HEADERS += \
    segment3d.h \
    line3d.h \
    vector3d.h \
    sphere3d.h \
    plane3d.h \
    Testlib.h \
    algorithms.h \
    tests.h
