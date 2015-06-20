#include "sphere.hpp"

Sphere::Sphere() : Shape{}, center_{glm::vec3{0.0, 0.0, 0.0}}, radius_{0.0} {} 
Sphere::Sphere(glm::vec3 const& c, double r) : 
  Shape{}, center_{c}, radius_{r} {}

Sphere::Sphere(Color const& clr, std::string const& n, glm::vec3 const& c, double r) :
    Shape{clr, n}, center_{c}, radius_{r} {}

/* virtual */ double Sphere::area() const {
  return 4.0 * PI * (radius_ * radius_);
}

/* virtual */ double Sphere::volume() const {
    return 4.0/3.0 * PI * (radius_ * radius_ * radius_);
}