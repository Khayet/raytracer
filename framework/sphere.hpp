#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"

const double PI  = 3.141592653589793;


class Sphere: public Shape {

public:
  Sphere();
  Sphere(glm::vec3 const& c, double r);
  Sphere(Material const& material, std::string const& n, glm::vec3 const& c, double r);
  Sphere(glm::vec3 const&, double, Material const&, std::string const&);
  ~Sphere();

  glm::vec3 center() const { return center_; }
  double radius() const { return radius_; }

  /* virtual */ double area() const /* override */;
  /* virtual */ double volume() const /* override */;

  /* virtual */ std::ostream& print(std::ostream&) const /* override */;

  bool intersect(Ray const&, float&)const;

private:
  glm::vec3 center_;
  double radius_;
};

#endif
