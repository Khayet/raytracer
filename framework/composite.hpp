#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include "shape.hpp"
#include <memory>
#include <vector>

class Composite: public Shape {
public:
  Composite();
  Composite(std::vector<std::shared_ptr<Shape>> shapes);
  ~Composite();

/* virtual */ double area() const;
/* virtual */ double volume() const;
  std::vector<std::shared_ptr<Shape>> shapes() const { return shapes_; }
  bool intersect(Ray const&) const;
  bool intersect(Ray const&, float& dist) const;
  glm::vec3 intersect_normal(glm::vec3 const& intersection) const;
  std::shared_ptr<Shape> get_children();
  void add(std::vector<std::shared_ptr<Shape>> const& shape_ptr);
  void remove(std::vector<std::shared_ptr<Shape>> const& shape_ptr);
  
private:
  std::vector<std::shared_ptr<Shape>> shapes_;
};

#endif
