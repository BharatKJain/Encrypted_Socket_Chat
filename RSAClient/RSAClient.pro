QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RSAClient
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
        stdafx.h

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
