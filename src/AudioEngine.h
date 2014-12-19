#pragma once

#include <chrono>
#include <thread>

#include "portaudio.h"

#include <QObject>
#include <QDebug>

#include <sfrp/behavior.hpp>

#include "Surface.h"

class AudioEngine : public QObject
{
  Q_OBJECT

public:

  typedef struct
  {
    float left;
    float right;
  }
  AudioSample;

  explicit AudioEngine( const Surface&, QObject *parent = 0);
  ~AudioEngine() = default;


// --------------------------------------------------------------------------------------------------------------------

public slots:
  void start();
  void stop();

  void startStop();

// --------------------------------------------------------------------------------------------------------------------

private:
  int pa_callback( const void *inputBuffer,
                            void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData
                            );

  bool m_running;
  std::unique_ptr<std::thread> m_thread;
  Surface m_surface;
};

