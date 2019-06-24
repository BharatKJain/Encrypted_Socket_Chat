#-------------------------------------------------
#
# Project created by QtCreator 2019-06-03T19:43:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EncCliQT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Qt/5.12.3/gcc_64/lib/release/ -lcryptopp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Qt/5.12.3/gcc_64/lib/debug/ -lcryptopp
else:unix: LIBS += -L$$PWD/../../../../Qt/5.12.3/gcc_64/lib/ -lcryptopp

INCLUDEPATH += $$PWD/../../../../Qt/5.12.3/gcc_64/include
DEPENDPATH += $$PWD/../../../../Qt/5.12.3/gcc_64/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Qt/5.12.3/gcc_64/lib/release/libcryptopp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Qt/5.12.3/gcc_64/lib/debug/libcryptopp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Qt/5.12.3/gcc_64/lib/release/cryptopp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../Qt/5.12.3/gcc_64/lib/debug/cryptopp.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../Qt/5.12.3/gcc_64/lib/libcryptopp.a
