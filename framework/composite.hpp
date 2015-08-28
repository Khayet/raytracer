#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include "shape.hpp"
#include "raystructure.hpp"
#include <memory>
#include <vector>

class Composite: public Shape {
public:
  Composite();
  Composite(std::vector<std::shared_ptr<Shape>> shapes);
  Composite(Composite const& copy_composite); 
  ~Composite();

  /* virtual */ double area() const /* override */;
  /* virtual */ double volume() const /* override */;
  /* virtual */ std::ostream& print(std::ostream&) const /* override */;

  bool intersect(Ray const&) const;
  bool intersect(Ray const&, float& dist) const;
  glm::vec3 intersect_normal(Raystructure const& raystructure) const;
  std::vector<std::shared_ptr<Shape>> get_children();
  void add(std::shared_ptr<Shape> const& shared_shape);
  void remove(std::shared_ptr<Shape> const& shared_shape);
  
private:
  std::vector<std::shared_ptr<Shape>> children_;
};

#endif
