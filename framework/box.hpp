#ifndef BOX_HPP
#define BOX_HPP

#include <cmath>
#include <algorithm>
#include "shape.hpp"

class Box: public Shape {
//
public:
  Box();
  Box(glm::vec3 const& min, glm::vec3 const& max);
  Box(Material const& material, std::string const& n,
    glm::vec3 const& min, glm::vec3 const& max);
  ~Box();

  glm::vec3 min() const { return min_; }
  glm::vec3 max() const { return max_; }
 
  /* virtual */ double area() const /* override */;
  /* virtual */ double volume() const /* override */;

  /* virtual */ std::ostream& print(std::ostream&) const /* override */;

  bool intersect(Ray const&) const;
  bool intersect(Ray const&, float& dist) const;
  bool intersect(
    Ray const& ray, 
    float& dist, 
    std::shared_ptr<Shape> & ptr) const;
  glm::vec3 intersect_normal(Raystructure const& raystructure) const;
  
private:
  glm::vec3 min_;
  glm::vec3 max_;
};

#endif
