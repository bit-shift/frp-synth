#pragma once

#include <sfrp/behavior.hpp>

#include "sfrputil.h"

namespace DSP {

  using namespace sfrp;

  Behavior<float> osc_sin( Behavior<float> freq ) {
    return Behavior<float>::fromValuePullFunc( [ freq ] ( double time ) {
      auto frequency = freq.pull( time );
      if( frequency )
      {
        return boost::make_optional( frequency.get() * 23.0f );
      }
      return boost::make_optional( 23.0f );
    });
  }
}

