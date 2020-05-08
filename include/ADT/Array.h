#pragma once

#include <cstddef>
#include <utility>
#include <algorithm>

template<class T, size_t sz>
class RawArray {
  T data[sz];

  void fill(size_t i) {}
  template<class ArgT, class... Args>
  void fill(size_t i, ArgT argI, Args... values) {
    data[i] = argI;
    fill(i+1,values...);
  }

public:
  RawArray() {}

  template<class... Args>
  RawArray(Args... values) {
    //in order to accept values of different types (e.g., int, size_t, ...)
    //fill in the data recursively via variadic templates 
    fill(0, values...);
  }

  using value_type = T;
  using iterator = value_type *;
  using const_iterator = const value_type *;

  constexpr size_t size() const { return sz; }
  //size_t size() const { return sz; }
  iterator begin() { return data; }
  iterator end() { return data+sz; }
  const_iterator begin() const { return data; }
  const_iterator end() const { return data+sz; }

  value_type &operator[](const size_t index) {
    return data[index];
  }

  const value_type &operator[](const size_t index) const {
    return data[index];
  }
};

template<class T, class IteratorT = T *>
class ArrayRef {
  IteratorT first;
  size_t sz;

public:
  using value_type = T;
  using iterator = IteratorT;
  using const_iterator = const IteratorT;

  ArrayRef(IteratorT first, size_t size) : first(first), sz(size) {}
  ArrayRef() : first(nullptr), sz(0) {}
  void reference(IteratorT first, size_t size) {
    this->first = first;
    this->sz = size;
  }
  template<class AnyT>
  void reference(AnyT a) {
    this->first = a.begin();
    this->sz = a.size();
  }
  size_t size() const { return sz; }
  iterator begin() { return first; }
  iterator end() { return first+sz; }
  const_iterator begin() const { return first; }
  const_iterator end() const { return first+sz; }

  value_type &operator[](const size_t index) {
    return first[index];
  }

  const value_type &operator[](const size_t index) const {
    return first[index];
  }
};

template<class T, size_t N>
class NArray {
  RawArray<size_t, N> dims;
  size_t numElements;
  T *data;

  void pushDim(size_t i) {}
  template<class ArgT, class... Args>
  void pushDim(size_t i, ArgT argI, Args... dimentions) {
    dims[i] = argI;
    numElements *= argI;
    pushDim(i+1,dimentions...);
  }

  size_t sumIndices(size_t i) { return 0; }  
  template<class ArgT, class... Args>
  size_t sumIndices(size_t i, ArgT argI, Args... indices) {
    size_t tmp = argI;
    for (size_t j = i+1; j<N; j++) {
      tmp *= dims[j];
    }
    return tmp + sumIndices(i+1, indices...);
  }

public:
  using value_type = T;
  using iterator = value_type *;
  using const_iterator = const value_type *;

  NArray() : data(nullptr) {}

  template<class... Args>
  bool allocate(Args... dimentions) {
    if (data) return false;

    numElements = 1;
    pushDim(0,dimentions... );
    
    data = new T[numElements];
    return data!=nullptr;
  }

  void release() {
    if(data) delete []data;

    data = nullptr;
  }

  size_t size() const { return numElements; }
  const size_t size(const size_t d) const { return dims[d]; }

  iterator begin() { return data; }
  iterator end() { return data+size(); }
  const_iterator begin() const { return data; }
  const_iterator end() const { return data+size(); }

  T &operator[](size_t index) {
    return data[index];
  }

  template<class... Args>
  T &at(Args... indices) {
    size_t index = sumIndices(0,indices... );
    return data[index];
  }

};
