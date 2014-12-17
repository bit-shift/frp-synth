TEMPLATE = app

QT += qml quick widgets

SOURCES += src/main.cpp \
    src/AudioEngine.cpp

RESOURCES += qml.qrc

top_srcdir=$$PWD
top_builddir=$$shadowed($$PWD)


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

QMAKE_CXXFLAGS += -std=c++1y

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/AudioEngine.h



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/sbase/build/release/ -lsfrp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/sbase/build/debug/ -lsfrp
else:unix: LIBS += -L$$PWD/../lib/sbase/build/ -lsfrp

INCLUDEPATH += $$PWD/../lib/sbase/include
DEPENDPATH += $$PWD/../lib/sbase/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/sbase/build/release/libsfrp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/sbase/build/debug/libsfrp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/sbase/build/release/sfrp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/sbase/build/debug/sfrp.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/sbase/build/libsfrp.a
