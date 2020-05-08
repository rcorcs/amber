#pragma once

#include "Vector.h"

#include <cstdint>

const size_t RED = 0;
const size_t GREEN = 1;
const size_t BLUE = 2;
const size_t ALPHA = 3;

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


  typename ArrayTy::value_type &value() { return ArrayTy::operator[](0); }

  typename ArrayTy::value_type &value(typename ArrayTy::value_type val) { return value() = val; }

};

template<class ArrayTy>
class PixelAccessTrait<3, ArrayTy> : public ArrayTy {
public:
  PixelAccessTrait() {}
  template<class... Args>
  PixelAccessTrait(Args... values) : ArrayTy(values...) {}


  typename ArrayTy::value_type &red() { return ArrayTy::operator[](0); }
  typename ArrayTy::value_type &green() { return ArrayTy::operator[](1); }
  typename ArrayTy::value_type &blue() { return ArrayTy::operator[](2); }

  typename ArrayTy::value_type &red(typename ArrayTy::value_type val) { return red() = val; }
  typename ArrayTy::value_type &green(typename ArrayTy::value_type val) { return green() = val; }
  typename ArrayTy::value_type &blue(typename ArrayTy::value_type val) { return blue() = val; }
};

template<class ArrayTy>
class PixelAccessTrait<4, ArrayTy> : public ArrayTy {
public:
  PixelAccessTrait() {}
  template<class... Args>
  PixelAccessTrait(Args... values) : ArrayTy(values...) {}

  typename ArrayTy::value_type &red() { return ArrayTy::operator[](0); }
  typename ArrayTy::value_type &green() { return ArrayTy::operator[](1); }
  typename ArrayTy::value_type &blue() { return ArrayTy::operator[](2); }
  typename ArrayTy::value_type &alpha() { return ArrayTy::operator[](3); }

  typename ArrayTy::value_type &red(typename ArrayTy::value_type val) { return red() = val; }
  typename ArrayTy::value_type &green(typename ArrayTy::value_type val) { return green() = val; }
  typename ArrayTy::value_type &blue(typename ArrayTy::value_type val) { return blue() = val; }
  typename ArrayTy::value_type &alpha(typename ArrayTy::value_type val) { return alpha() = val; }
};


template<size_t size>
using Pixel = VectorTraits< PixelAccessTrait< size, RawArray<uint8_t,size> > >;

using Grey = Pixel<1>;
using RGB  = Pixel<3>;
using RGBA = Pixel<4>;

using PixelRef = VectorRef<uint8_t>;
