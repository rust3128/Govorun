QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
win32: RC_ICONS = $$PWD/Images/govorun.ico

SOURCES += \
    AzsNetworkDialog/azsnetworkdialog.cpp \
    AzsNetworkDialog/azsnetworkmodel.cpp \
    AzsNetworkDialog/editazsnetworkdialog.cpp \
    AzsNetworkDialog/logodelegate.cpp \
    DataBase/database.cpp \
    Firms/editfirmsdialog.cpp \
    Firms/firmsdialog.cpp \
    Firms/mymodelfirms.cpp \
    GlobalSettings/globalsettings.cpp \
    LoggingCategories/loggingcategories.cpp \
    OptionsDialog/optionsdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AzsNetworkDialog/azsnetworkdialog.h \
    AzsNetworkDialog/azsnetworkmodel.h \
    AzsNetworkDialog/editazsnetworkdialog.h \
    AzsNetworkDialog/logodelegate.h \
    DataBase/database.h \
    Firms/editfirmsdialog.h \
    Firms/firmsdialog.h \
    Firms/mymodelfirms.h \
    GlobalSettings/globalsettings.h \
    LoggingCategories/loggingcategories.h \
    OptionsDialog/optionsdialog.h \
    mainwindow.h

FORMS += \
    AzsNetworkDialog/azsnetworkdialog.ui \
    AzsNetworkDialog/editazsnetworkdialog.ui \
    Firms/editfirmsdialog.ui \
    Firms/firmsdialog.ui \
    OptionsDialog/optionsdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourse.qrc
