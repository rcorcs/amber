#pragma once

#include "Math/Vector.h"

#include "Force.h"

template<size_t dim>
class Body : public Vector<float, dim> {
  using Base = Vector<float, dim>;
  Vector<float, dim> a; //acceleration
  float m;
public:

  template<class... Args>
  Body(Args... values) : Base(values...), a(0,0), m(1) {}

  Body () : Base(0,0), a(0,0), m(1) {}

  float mass() { return m; }

  Vector<float, dim> &acceleration() { return a; }

  void apply(Force<dim> force) {
    acceleration().add(force.div(mass()));
  }

  void move() {
    Base::add(acceleration());
  }
};

