#include "PortAudio.h"

// --------------------------------------------------------------------------------------------------------------------

PortAudio::PortAudio()
  : m_stream(  )
{
  qDebug() << "PortAudio::PortAudio()";

  auto error = Pa_Initialize();
  if( error != paNoError )
    qDebug() << "PortAudio::PortAudio() - Could not initialize portaudio! Error: " << error;
}

// --------------------------------------------------------------------------------------------------------------------

PortAudio::~PortAudio()
{
  qDebug() << "PortAudio::~PortAudio()";
}

// --------------------------------------------------------------------------------------------------------------------

void PortAudio::start()
{
  auto error = Pa_StartStream( m_stream );
  if( error != paNoError )
    qDebug() << "PortAudio::stop() - Error: " << Pa_GetErrorText( error );
}

// --------------------------------------------------------------------------------------------------------------------

void PortAudio::stop()
{
  auto error = Pa_Terminate();
  if( error != paNoError )
    qDebug() << "PortAudio::stop() - Error: " << Pa_GetErrorText( error );
}
