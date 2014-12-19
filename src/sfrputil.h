#pragma once

#include <sfrp/behavior.hpp>

namespace sfrp {

  template<typename ValueType>
  sfrp::Behavior<ValueType> operator *( sfrp::Behavior<ValueType> lhs,
                                        sfrp::Behavior<ValueType> rhs ) {
    return sfrp::Behavior<ValueType>::fromValuePullFunc([lhs, rhs](double time)
                                                        ->boost::optional<ValueType> {
      boost::optional<ValueType> lhsVal = lhs.pull(time);
      boost::optional<ValueType> rhsVal = rhs.pull(time);
      if (lhsVal && rhsVal)
        return boost::make_optional(*lhsVal * *rhsVal);
      else
        return boost::none;
    });
  }
}

