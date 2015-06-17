#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"

const double PI  = 3.141592653589793238463;


class Sphere: public Shape {

public:
  Sphere(): center_{glm::vec3{0.0, 0.0, 0.0}}, radius_{0.0} {} 
  Sphere(glm::vec3 const& c, double r): center_{c}, radius_{r} {}


  glm::vec3 center() const {
    return center_;
  }

  double radius() const {
    return radius_;
  }

  /* virtual */ double area() const {
  }

  /* virtual */ double volume() const {
    //return (4/3) * PI * (radius_ * radius_ * radius_);
  }

private:
  glm::vec3 center_;
  double radius_;
};

#endif