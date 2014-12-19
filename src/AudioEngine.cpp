#include "AudioEngine.h"

#include "sfrputil.h"

#include "dsp.h"
// --------------------------------------------------------------------------------------------------------------------

AudioEngine::AudioEngine( const Surface& surface, QObject *parent )
  : QObject( parent ),
    m_running( false ),
    m_thread( nullptr ),
    m_surface( surface )
{

}

// --------------------------------------------------------------------------------------------------------------------

void AudioEngine::start()
{
  m_running = true;

  auto thread = new std::thread( [this] () {
    //! Main sound synthesis! Pull forrest, pull!

  });
  m_thread.reset( thread );
}

// --------------------------------------------------------------------------------------------------------------------

void AudioEngine::stop()
{
  m_running = false;

  if ( !!m_thread ) {
    m_thread.get()->join();
  }
  m_thread.release();
}

// --------------------------------------------------------------------------------------------------------------------

void AudioEngine::startStop()
{
  if ( !m_running ) {
    start();
  } else {
    stop();
  }
}

// --------------------------------------------------------------------------------------------------------------------

int AudioEngine::pa_callback( const void *inputBuffer,
                        void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData
                        )
{
  // Cast data passed through stream to our structure.
  AudioSample *data = ( AudioSample* ) userData;
  float *out = ( float* ) outputBuffer;

  // Prevent unused variable warning.
  ( void ) inputBuffer;

  unsigned int i;

  for( i = 0; i < framesPerBuffer; i++ )
  {
    // left & right
    *out++ = data->left;
    *out++ = data->right;

    // Generate simple sawtooth phaser that ranges between -1.0 and 1.0.
    data->left += 0.01f;

    // When signal reaches top, drop back down.
    if( data->left >= 1.0f ) data->left -= 2.0f;

    // higher pitch so we can distinguish left and right.
    data->right += 0.03f;

    if( data->right >= 1.0f ) data->right -= 2.0f;

    /*
      auto now = std::chrono::system_clock::now().time_since_epoch().count();

      Behavior<float> oscComp = DSP::osc_sin( m_surface.frequencyControl() );

      auto next = oscComp.pull( now );
      if ( next ) qDebug() << next.value();

      std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
    */
  }
  return 0;
}
