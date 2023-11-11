QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23


SOURCES += \
    ../stateWidget/statewidget.cpp \
    ../stateWidget/safety.cpp \
    ../ICommand/callcommand.cpp \
    ../ICommand/commentcommand.cpp \
    ../ICommand/emptycommand.cpp \
    ../ICommand/ifcommand.cpp \
    ../ICommand/jumpcommand.cpp \
    ../ICommand/mathcommand.cpp \
    ../ICommand/movecommand.cpp \
    ../ICommand/waitcommand.cpp \
    ../ICommand/icommand.cpp \
    ../RegisterWidget/registerbase.cpp \
    jsonloader.cpp \
    jsonmodule.cpp \
    main.cpp

HEADERS += \
    ../stateWidget/statewidget.h \
    ../stateWidget/safety.h \
    ../ICommand/callcommand.h \
    ../ICommand/commentcommand.h \
    ../ICommand/emptycommand.h \
    ../ICommand/icommand.h \
    ../ICommand/ifcommand.h \
    ../ICommand/jumpcommand.h \
    ../ICommand/mathcommand.h \
    ../ICommand/movecommand.h \
    ../ICommand/waitcommand.h \
    ../RegisterWidget/registerbase.h \
    jsonloader.h \
    jsonmodule.h

FORMS += \
    ../stateWidget/statewidget.ui \


RESOURCES += \
../resource/resource.qrc
ICON = ../resource/icon/spacex.icns

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
