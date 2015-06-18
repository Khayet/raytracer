#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"

const double PI  = 3.141592653589793;

class Sphere: public Shape {

public:
  Sphere() : Shape{}, center_{glm::vec3{0.0, 0.0, 0.0}}, radius_{0.0} {} 
  Sphere(glm::vec3 const& c, double r) : Shape{}, center_{c}, radius_{r} {}

  Sphere(Color const& clr, std::string const& n, glm::vec3 const& c, double r) :
    Shape{clr, n}, center_{c}, radius_{r} {}

  glm::vec3 center() const { return center_; }
  double radius() const { return radius_; }

  /* virtual */ double area() const override {
    return 4.0 * PI * (radius_ * radius_);
  }

  /* virtual */ double volume() const override {
    return 4.0/3.0 * PI * (radius_ * radius_ * radius_);
  }

private:
  glm::vec3 center_;
  double radius_;
};

#endif