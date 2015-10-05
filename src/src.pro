HEADERS += \
    init_window.h \
    utility.h \
    living_fractions.h \
    config_window_base.h

SOURCES += \
    init_window.cpp \
    main.cpp \
    living_fractions.cpp \
    config_window_base.cpp

QT += \
    widgets

CONFIG += \
    c++11

QMAKE_MAC_SDK = macosx10.11
