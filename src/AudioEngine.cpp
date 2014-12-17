#include "AudioEngine.h"

#include <QDebug>

#include <sfrp/behavior.hpp>

//!--------------------------------------------------------------------------------------------------------------------

AudioEngine::AudioEngine( QObject* rootObject, QObject *parent )
    : QObject( parent ),
      m_root( rootObject ),
      m_running( false ),
      m_thread( nullptr )
{
}

//!--------------------------------------------------------------------------------------------------------------------

AudioEngine::~AudioEngine()
{
}

//!--------------------------------------------------------------------------------------------------------------------

void AudioEngine::start()
{
    m_running = true;

    auto thread = new std::thread( [this] () {
        while ( m_running ) {

            //!--------------------------------------------------------------------------------------------------------

            auto frequencyControl = m_root->findChild<QObject*>( "frequencyControl" );

            sfrp::Behavior<float> freqKnob = sfrp::Behavior<float>::fromValuePullFunc( [frequencyControl] ( double time )
            {
                return boost::make_optional(frequencyControl->property( "value" ).toFloat());
            });

            boost::optional<float> value = freqKnob.pull( 0.0f);
            if ( value )
            {
                qDebug() << value.value();
            }

            std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );

            //!--------------------------------------------------------------------------------------------------------
        }
    });
    m_thread.reset( thread );
}

//!--------------------------------------------------------------------------------------------------------------------

void AudioEngine::stop()
{
    m_running = false;

    if ( !!m_thread ) {
        m_thread.get()->join();
    }
    m_thread.release();
}

//!--------------------------------------------------------------------------------------------------------------------

void AudioEngine::startStop()
{
    if ( !m_running ) {
        start();
    } else {
        stop();
    }
}


