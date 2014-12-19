#pragma once

#include <portaudio.h>

#include <QDebug>

class PortAudio
{
public:
  PortAudio();
  ~PortAudio();

  void start();
  void stop();

private:
  PaStream* m_stream;
};
