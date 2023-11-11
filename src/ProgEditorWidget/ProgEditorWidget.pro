QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23
#QMAKE_MACOSX_DEPLOYMENT_TARGET = 14.0

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    programmeditorwidget.cpp \
    main.cpp \
    programmmodel.cpp \
    ../ICommand/callcommand.cpp \
    ../ICommand/commentcommand.cpp \
    ../ICommand/emptycommand.cpp \
    ../ICommand/ifcommand.cpp \
    ../ICommand/jumpcommand.cpp \
    ../ICommand/mathcommand.cpp \
    ../ICommand/movecommand.cpp \
    ../ICommand/waitcommand.cpp \
    ../ICommand/icommand.cpp \
    ../JSONmodule/jsonloader.cpp \
    ../JSONmodule/jsonmodule.cpp \
    ../stateWidget/statewidget.cpp \
    ../stateWidget/safety.cpp \
    ../RegisterWidget/registerbase.cpp \


HEADERS += \
    programmeditorwidget.h \
    programmmodel.h \
    ../ICommand/callcommand.h \
    ../ICommand/commentcommand.h \
    ../ICommand/emptycommand.h \
    ../ICommand/icommand.h \
    ../ICommand/ifcommand.h \
    ../ICommand/jumpcommand.h \
    ../ICommand/mathcommand.h \
    ../ICommand/movecommand.h \
    ../ICommand/waitcommand.h \
    ../JSONmodule/jsonloader.h \
    ../JSONmodule/jsonmodule.h \
    ../stateWidget/statewidget.h \
    ../stateWidget/safety.h \
    ../RegisterWidget/registerbase.h \

FORMS += \
    programmeditorwidget.ui \
    ../stateWidget/statewidget.ui


RESOURCES += \
../resource/resource.qrc
ICON = ../resource/icon/spacex.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



