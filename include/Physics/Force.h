#pragma once

#include "Math/Vector.h"

template<size_t dim>
using Force = Vector<float,dim>;

class Force2D {
public:
  static Force<2> left(float magnitude) {
    return Force<2>(-magnitude, 0);
  }
  static Force<2> right(float magnitude) {
    return Force<2>(magnitude, 0);
  }
  static Force<2> up(float magnitude) {
    return Force<2>(0, -magnitude);
  }
  static Force<2> down(float magnitude) {
    return Force<2>(0, magnitude);
  }
};

