#include "Surface.h"

// --------------------------------------------------------------------------------------------------------------------

Surface::Surface( QObject *qml )
  : m_qml( qml )
{
  m_frequencyControl  = qml_behavior<float>( "frequencyControl" );
  m_waveformControl   = qml_behavior<int>( "waveformControl" );
}

// --------------------------------------------------------------------------------------------------------------------
template<typename ValueType>
Behavior<ValueType> Surface::qml_behavior( const std::string& objectName )
{
  Behavior<ValueType> frpKnob = Behavior<ValueType>::fromValuePullFunc( [ this, objectName ] ( double time )
  {
    return boost::make_optional( component_value<ValueType>( objectName ) );
  });
  return frpKnob;
}

// --------------------------------------------------------------------------------------------------------------------

template<typename ValueType>
ValueType Surface::component_value( const std::string& objectName )
{
  auto comp = component( objectName );
  if( comp )
  {
    return value<ValueType>( *component( objectName ).get() );
  }
  return 0.0f;
}

// --------------------------------------------------------------------------------------------------------------------

template<typename ValueType>
ValueType Surface::value( const QObject& component )
{
  return component.property( "value" ).value<ValueType>();
}

// --------------------------------------------------------------------------------------------------------------------

boost::optional<QObject*> Surface::component( const std::string& objectName )
{
  return boost::make_optional( m_qml->findChild<QObject*>( QString::fromStdString( objectName ) ) );
}


