
#pragma once

#include "ADT/Array.h"

#include <cstddef>
#include <utility>


class VectorOperators {
public:

  template<class T1, class T2>
  static T1 &copy(T1 &v1, T2 &v2) {
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    while (it1!=v1.end()) {
      *it1 = *it2;
      it1++;
      it2++;
    }
    return v1;
  }

  template<class T1, class T2>
  static T1 &add(T1 &v1, T2 &v2) {
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    while (it1!=v1.end()) {
      *it1 += *it2;
      it1++;
      it2++;
    }
    return v1;
  }

  template<class T1, class T2>
  static T1 &sub(T1 &v1, T2 &v2) {
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    while (it1!=v1.end()) {
      *it1 -= *it2;
      it1++;
      it2++;
    }
    return v1;
  }

  template<class T1, class T2>
  static T1 &mult(T1 &v1, T2 &v2) {
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    while (it1!=v1.end()) {
      *it1 *= *it2;
      it1++;
      it2++;
    }
    return v1;
  }

  template<class T1, class T2>
  static T1 &div(T1 &v1, T2 &v2) {
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    while (it1!=v1.end()) {
      *it1 /= *it2;
      it1++;
      it2++;
    }
    return v1;
  }

  template<class T1, class T2>
  static typename T1::value_type dot(T1 &v1, T2 &v2) {
    typename T1::value_type sum(0);
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    while (it1!=v1.end()) {
      sum += (*it1) * (*it2);
      it1++;
      it2++;
    }
    return sum;
  }

};

template<size_t sz, class ArrayTy>
class VectorAccessTrait : public ArrayTy {
public:
  VectorAccessTrait() {}
  template<class... Args>
  VectorAccessTrait(Args... values) : ArrayTy(values...) {}
};

template<class ArrayTy>
class VectorAccessTrait<2, ArrayTy> : public ArrayTy {
public:
  VectorAccessTrait() {}
  template<class... Args>
  VectorAccessTrait(Args... values) : ArrayTy(values...) {}


  typename ArrayTy::value_type &x() { return ArrayTy::operator[](0); }
  typename ArrayTy::value_type &y() { return ArrayTy::operator[](1); }

  typename ArrayTy::value_type &x(typename ArrayTy::value_type val) { return ArrayTy::operator[](0) = val; }
  typename ArrayTy::value_type &y(typename ArrayTy::value_type val) { return ArrayTy::operator[](1) = val; }
};

template<class ArrayTy>
class VectorAccessTrait<3, ArrayTy> : public ArrayTy {
public:
  VectorAccessTrait() {}
  template<class... Args>
  VectorAccessTrait(Args... values) : ArrayTy(values...) {}

  typename ArrayTy::value_type &x() { return ArrayTy::operator[](0); }
  typename ArrayTy::value_type &y() { return ArrayTy::operator[](1); }
  typename ArrayTy::value_type &z() { return ArrayTy::operator[](2); }

  typename ArrayTy::value_type &x(typename ArrayTy::value_type val) { return ArrayTy::operator[](0) = val; }
  typename ArrayTy::value_type &y(typename ArrayTy::value_type val) { return ArrayTy::operator[](1) = val; }
  typename ArrayTy::value_type &z(typename ArrayTy::value_type val) { return ArrayTy::operator[](2) = val; }
};

template<class ArrayTy>
class VectorAccessTrait<4, ArrayTy> : public ArrayTy {
public:
  VectorAccessTrait() {}
  template<class... Args>
  VectorAccessTrait(Args... values) : ArrayTy(values...) {}

  typename ArrayTy::value_type &x() { return ArrayTy::operator[](0); }
  typename ArrayTy::value_type &y() { return ArrayTy::operator[](1); }
  typename ArrayTy::value_type &z() { return ArrayTy::operator[](2); }
  typename ArrayTy::value_type &w() { return ArrayTy::operator[](3); }

  typename ArrayTy::value_type &x(typename ArrayTy::value_type val) { return ArrayTy::operator[](0) = val; }
  typename ArrayTy::value_type &y(typename ArrayTy::value_type val) { return ArrayTy::operator[](1) = val; }
  typename ArrayTy::value_type &z(typename ArrayTy::value_type val) { return ArrayTy::operator[](2) = val; }
  typename ArrayTy::value_type &w(typename ArrayTy::value_type val) { return ArrayTy::operator[](3) = val; }
};

template<class ArrayTy>
class VectorTraits : public ArrayTy {
using this_type = VectorTraits<ArrayTy>;
public: 

  VectorTraits() {}

  template<class... Args>
  VectorTraits(Args... values) : ArrayTy(values...) {}

  template<class AnyVecT>
  this_type &add(AnyVecT &v) {
    return VectorOperators::add(*this, v);
  }

  template<class AnyVecT>
  this_type operator+(AnyVecT &v) {
    this_type ans = *this;
    return VectorOperators::add(ans, v);
  }

  template<class AnyVecT>
  this_type &sub(AnyVecT &v) {
    return VectorOperators::sub(*this, v);
  }

  template<class AnyVecT>
  this_type operator-(AnyVecT &v) {
    this_type ans = *this;
    return VectorOperators::sub(ans, v);
  }

  template<class AnyVecT>
  this_type &mult(AnyVecT &v) {
    return VectorOperators::mult(*this, v);
  }

  template<class AnyVecT>
  this_type operator*(AnyVecT &v) {
    this_type ans = *this;
    return VectorOperators::mult(ans, v);
  }

  template<class AnyVecT>
  this_type &div(AnyVecT &v) {
    return VectorOperators::div(*this, v);
  }

  template<class AnyVecT>
  this_type operator/(AnyVecT &v) {
    this_type ans = *this;
    return VectorOperators::div(ans, v);
  }

  template<class AnyVecT>
  typename ArrayTy::value_type dot(AnyVecT &v) {
    return VectorOperators::dot(*this, v);
  }

};

template<class T, size_t sz>
using Vector = VectorTraits< VectorAccessTrait< sz, RawArray<T,sz> > >;


template<class T, class IteratorT=T*>
class VectorRef : public VectorTraits< ArrayRef<T, IteratorT> > {
public:
  VectorRef(IteratorT first, size_t sz) {
    ArrayRef<T, IteratorT>::reference(first,sz);
  }
  template<class AnyT>
  VectorRef(AnyT &a) {
    ArrayRef<T, IteratorT>::reference(a.begin(),a.size());
  }
  VectorRef() {}
};

using Vec2i = Vector<int,2>;
using Vec3i = Vector<int,3>;
using Vec4i = Vector<int,4>;

using Vec2f = Vector<float,2>;
using Vec3f = Vector<float,3>;
using Vec4f = Vector<float,4>;
using Quaternion = Vec4f;

