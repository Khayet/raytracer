#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <ostream>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include "color.hpp"
#include "ray.hpp"

class Shape {

public:
  Shape();
  Shape(Color const&, std::string const&);

  ~Shape();

  Color color() const { return color_; }
  std::string name() const { return name_; }

  virtual double area() const = 0;
  virtual double volume() const = 0;

  virtual std::ostream& print(std::ostream&) const;

private:
  std::string name_;
  Color color_;
};

std::ostream& operator<<(std::ostream&, Shape const&);

#endif 
