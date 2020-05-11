
#pragma once

#include "Physics/Body.h"

template<size_t dim>
class Model : public Body<dim> {
};

class Box2D : public Model<2> {

};