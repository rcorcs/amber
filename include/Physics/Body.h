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

template<size_t dim>
class BoxBody : public Body<dim>, public Dimentional<float,dim> {
public:

  bool collision(BoxBody<dim> &other) {
    const float x = Body<dim>::x();
    const float y = Body<dim>::y();
    const float halfWidth = Dimentional<float,dim>::width()/2.f;
    const float halfHeight = Dimentional<float,dim>::height()/2.f;

    if (y+halfHeight < other.y()-other.height()/2.f) return false;
    if (y-halfHeight > other.y()+other.height()/2.f) return false;

    if (x+halfWidth < other.x()-other.width()/2.f) return false;
    if (x-halfWidth > other.x()+other.width()/2.f) return false;

    return true;
  }
};