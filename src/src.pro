HEADERS += \
    init_window.h \
    utility.h \
    living_fractions.h \
    config_window_base.h \
    cupcake_war.h \
    mlist.h \
    clock_game.h \
    order_of_operations.h \
    prefix_pogoda.h \
    teaching_tool.h \
    reading_game.h

SOURCES += \
    init_window.cpp \
    main.cpp \
    living_fractions.cpp \
    config_window_base.cpp \
    cupcake_war.cpp \
    mlist.cpp \
    clock_game.cpp \
    order_of_operations.cpp \
    prefix_pogoda.cpp \
    teaching_tool.cpp \
    reading_game.cpp

QT += \
    widgets

CONFIG += \
    c++11

QMAKE_MAC_SDK = macosx10.11

FORMS += \
    order_of_operations.ui \
    prefix_pogoda.ui \
    teaching_tool.ui \
    reading_game.ui
