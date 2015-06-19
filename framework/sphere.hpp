#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"

const double PI  = 3.141592653589793;


class Sphere: public Shape {

public:
  Sphere();
  Sphere(glm::vec3 const& c, double r);
  Sphere(Color const& clr, std::string const& n, glm::vec3 const& c, double r);

  glm::vec3 center() const { return center_; }
  double radius() const { return radius_; }

  /* virtual */ double area() const override;
  /* virtual */ double volume() const override;

private:
  glm::vec3 center_;
  double radius_;
};

#endif