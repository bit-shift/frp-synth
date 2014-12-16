TEMPLATE = app

QT += qml quick widgets

SOURCES += src/main.cpp \
    src/AudioEngine.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

QMAKE_CXXFLAGS += -std=c++1y

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/AudioEngine.h


