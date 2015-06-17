#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <glm/vec3.hpp>

class Shape {

public:
  virtual double area() const = 0;
  virtual double volume() const = 0;
};

#endif 