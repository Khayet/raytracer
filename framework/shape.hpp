#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <glm/vec3.hpp>
#include "color.hpp"

class Shape {

public:
  Shape() : color_{0.0, 0.0, 0.0}, name_{} {}
  Shape(Color const& c, std::string const& n) : color_{c}, name_{n} {}

  Color color() const { return color_; }
  std::string name() const { return name_; }

  virtual double area() const = 0;
  virtual double volume() const = 0;

private:
  std::string name_;
  Color color_;
};

#endif 