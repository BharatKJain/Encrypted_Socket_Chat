TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Sample.cpp \
        stdafx.cpp

HEADERS += \
    stdafx.h

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
