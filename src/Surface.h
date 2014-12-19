#pragma once

#include <QObject>
#include <QVariant>

#include <sfrp/behavior.hpp>

using sfrp::Behavior;

class Surface
{
public:

  // Ctor and Dtor
  explicit Surface( QObject* );
  ~Surface() = default;

  // Behaviors of QML controls
  Behavior<float> frequencyControl() { return m_frequencyControl; }
  Behavior<int> wavformControl() { return m_waveformControl; }

private:

  // Retrieves QML component by objectName and creates a Behavior of its value.
  template<typename ValueType>
  Behavior<ValueType> qml_behavior( const std::string& );

  // Retrieves a QML component's value.
  template<typename ValueType>
  ValueType component_value( const std::string& );

  // Retrieves the value of a QML component
  template<typename ValueType>
  ValueType value( const QObject& );

  // Looks up the QML component by objectName
  boost::optional<QObject*> component( const std::string& );

  // internal stuff
  QObject* m_qml;

  // Behaviors of QML controls
  Behavior<float> m_frequencyControl;
  Behavior<int> m_waveformControl;

};

