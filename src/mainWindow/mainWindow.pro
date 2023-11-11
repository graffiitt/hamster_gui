QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#QMAKE_MACOSX_DEPLOYMENT_TARGET = 14.0
CONFIG+=sdk_no_version_check
CONFIG += c++23

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ../ProgEditorWidget/programmeditorwidget.cpp \
    ../ProgEditorWidget/programmmodel.cpp \
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
    ../JSONmodule/jsonloader.cpp \
    ../JSONmodule/jsonmodule.cpp \
    ../ExectutorWidget/execturtorwidget.cpp \
    ../ExectutorWidget/iexecutor.cpp \
    ../ExectutorWidget/execcore.cpp \
     ../RegisterWidget/registerwidget.cpp \
     ../RegisterWidget/editorposeregister.cpp \
     ../RegisterWidget/registerdelegate.cpp \
     ../RegisterWidget/registerdto.cpp \
     ../RegisterWidget/registerbase.cpp \
     ../RegisterWidget/registermodel.cpp \
     ../CommunicateWidget/communicatorwidget.cpp \
     ../CommunicateWidget/serialtranslator.cpp



HEADERS += \
    mainwindow.h \
    ../ProgEditorWidget/programmeditorwidget.h \
    ../ProgEditorWidget/programmmodel.h \
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
    ../JSONmodule/jsonloader.h \
    ../JSONmodule/jsonmodule.h \
    ../ExectutorWidget/execturtorwidget.h \
    ../ExectutorWidget/iexecutor.h \
    ../ExectutorWidget/execcore.h \
    ../RegisterWidget/registerwidget.h \
    ../RegisterWidget/editorposeregister.h \
    ../RegisterWidget/registerdelegate.h \
    ../RegisterWidget/registerdto.h \
    ../RegisterWidget/registerbase.h \
    ../RegisterWidget/registermodel.h \
    ../CommunicateWidget/communicatorwidget.h \
    ../CommunicateWidget/serialtranslator.h





FORMS += \
    mainwindow.ui \
    ../ProgEditorWidget/programmeditorwidget.ui \
    ../stateWidget/statewidget.ui \
    ../ExectutorWidget/execturtorwidget.ui \
    ../RegisterWidget/registerwidget.ui \
    ../RegisterWidget/editorposeregister.ui \
    ../CommunicateWidget/communicatorwidget.ui



RESOURCES += \
    ../resource/resource.qrc
ICON = ../resource/icon/spacex.icns


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
