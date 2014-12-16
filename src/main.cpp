#include <iostream>

#include <chrono>
#include <thread>

#include <QApplication>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QDebug>

#include <src/AudioEngine.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //! QML initialization: start engine and load qml file
    QQmlApplicationEngine qmlEngine;
    qmlEngine.load( QUrl( QStringLiteral("qrc:/main.qml") ) );

    //! Query qml component for later use
    QObject* qmlMain = qmlEngine.rootObjects().first();
    QQuickItem* qmlStartStop = qmlMain->findChild<QQuickItem*>( "startStop" );


    //! The AudioEngine: This is the real FRP part of the application! When it starts, it infinitly pulls audio
    //! samples out of the audio graph defined using (sfrp-)Behaviors.
    AudioEngine audioEngine( qmlMain );


    //! Global non-FRP event handling: connect start/stop button for audio engine and
    //! assure stopping the engine on exit
    QObject::connect( qmlStartStop, SIGNAL(clicked()), &audioEngine, SLOT(startStop()));
    QObject::connect( &app, &QApplication::aboutToQuit, &audioEngine, &AudioEngine::stop );


    //! Execute and wait until exit signal received from UI
    return app.exec();
}

