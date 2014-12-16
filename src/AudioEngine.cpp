#include "AudioEngine.h"

#include <QDebug>

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
            auto frequencyControl = m_root->findChild<QObject*>( "frequencyControl" );

            if ( frequencyControl ) {
                qDebug() << frequencyControl->property( "value" ).toString();
            }
            std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
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


