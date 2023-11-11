TEMPLATE = app
CONFIG += console c++23
CONFIG -= app_bundle


SOURCES += \
        callcommand.cpp \
        commentcommand.cpp \
        emptycommand.cpp \
        icommand.cpp \
        ifcommand.cpp \
        jumpcommand.cpp \
        main.cpp \
        mathcommand.cpp \
        movecommand.cpp \
        waitcommand.cpp

HEADERS += \
    callcommand.h \
    commentcommand.h \
    emptycommand.h \
    icommand.h \
    ifcommand.h \
    jumpcommand.h \
    mathcommand.h \
    movecommand.h \
    waitcommand.h
