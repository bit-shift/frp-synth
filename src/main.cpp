#include <iostream>

#include <chrono>
#include <thread>

#include <QObject>
#include <QApplication>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QDebug>

#include <src/Surface.h>
#include <src/AudioEngine.h>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  //! QML initialization: start engine and load qml file
  QQmlApplicationEngine qmlEngine;
  qmlEngine.load( QUrl( QStringLiteral("qrc:/main.qml") ) );

  //! Query qml component for later use
  auto qml = qmlEngine.rootObjects().first();


  //! The AudioEngine: This is the real FRP part of the application! When it starts, it infinitly pulls audio
  //! samples out of the audio graph defined using (sfrp-)Behaviors.
  Surface surface( qml );
  AudioEngine audioEngine( surface );


  //! Global non-FRP event handling: connect start/stop button for audio engine and
  //! assure stopping the engine on exit
  QQuickItem* qmlStartStop = qml->findChild<QQuickItem*>( "startStop" );

  QObject::connect( qmlStartStop, SIGNAL(clicked()), &audioEngine, SLOT(startStop()));
  QObject::connect( &app, &QApplication::aboutToQuit, &audioEngine, &AudioEngine::stop );


  //! Execute and wait until exit signal received from UI
  return app.exec();
}

