#pragma once

#include "Math/Vector.h"

#include <cstdint>

template<size_t sz, class ArrayTy>
class PixelAccessTrait : public ArrayTy {
public:
  PixelAccessTrait() {}
  template<class... Args>
  PixelAccessTrait(Args... values) : ArrayTy(values...) {}
};

template<class ArrayTy>
class PixelAccessTrait<1, ArrayTy> : public ArrayTy {
public:
  PixelAccessTrait() {}
  template<class... Args>
  PixelAccessTrait(Args... values) : ArrayTy(values...) {}

  const typename ArrayTy::value_type value() const { return ArrayTy::operator[](0); }

  void value(typename ArrayTy::value_type val) { value() = val; }

};

template<class ArrayTy>
class PixelAccessTrait<3, ArrayTy> : public ArrayTy {
public:
  PixelAccessTrait() {}
  template<class... Args>
  PixelAccessTrait(Args... values) : ArrayTy(values...) {}


  const typename ArrayTy::value_type red() const { return ArrayTy::operator[](0); }
  const typename ArrayTy::value_type green() const { return ArrayTy::operator[](1); }
  const typename ArrayTy::value_type blue() const { return ArrayTy::operator[](2); }

  void red(typename ArrayTy::value_type val) { ArrayTy::operator[](0) = val; }
  void green(typename ArrayTy::value_type val) { ArrayTy::operator[](1) = val; }
  void blue(typename ArrayTy::value_type val) { ArrayTy::operator[](2) = val; }
};

template<class ArrayTy>
class PixelAccessTrait<4, ArrayTy> : public ArrayTy {
public:
  PixelAccessTrait() {}
  template<class... Args>
  PixelAccessTrait(Args... values) : ArrayTy(values...) {}

  const typename ArrayTy::value_type red() const { return ArrayTy::operator[](0); }
  const typename ArrayTy::value_type green() const { return ArrayTy::operator[](1); }
  const typename ArrayTy::value_type blue() const { return ArrayTy::operator[](2); }
  const typename ArrayTy::value_type alpha() const { return ArrayTy::operator[](3); }

  void red(typename ArrayTy::value_type val) { ArrayTy::operator[](0) = val; }
  void green(typename ArrayTy::value_type val) { ArrayTy::operator[](1) = val; }
  void blue(typename ArrayTy::value_type val) { ArrayTy::operator[](2) = val; }
  void alpha(typename ArrayTy::value_type val) { ArrayTy::operator[](3) = val; }
};

template<size_t size>
using Pixel = VectorTraits< PixelAccessTrait< size, RawArray<uint8_t,size> > >;

template<size_t size>
using RangePixel = VectorTraits< PixelAccessTrait< size, RawArray<float,size> > >;

using Grey = Pixel<1>;
using RGB  = Pixel<3>;
using RGBA = Pixel<4>;

using RangeGrey = RangePixel<1>;
using RangeRGB  = RangePixel<3>;
using RangeRGBA = RangePixel<4>;

using PixelRef = VectorRef<uint8_t>;
using RangePixelRef = VectorRef<float>;
