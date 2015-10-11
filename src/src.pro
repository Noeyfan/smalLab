HEADERS += \
    init_window.h \
    utility.h \
    living_fractions.h \
    config_window_base.h \
    cupcake_war.h \
    mlist.h \
    clock_game.h

SOURCES += \
    init_window.cpp \
    main.cpp \
    living_fractions.cpp \
    config_window_base.cpp \
    cupcake_war.cpp \
    mlist.cpp \
    clock_game.cpp

QT += \
    widgets

CONFIG += \
    c++11

QMAKE_MAC_SDK = macosx10.11
