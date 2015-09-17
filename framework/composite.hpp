#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include "shape.hpp"
#include "raystructure.hpp"
#include <memory>
#include <vector>
#include <unordered_map>

class Composite: public Shape {
public:
  Composite();
  Composite(std::unordered_map<std::string, std::shared_ptr<Shape>>);
  Composite(Composite const&);
  Composite(Material const&, std::string const&, std::unordered_map<std::string, std::shared_ptr<Shape>>);
  ~Composite();

  /* virtual */ double area() const /* override */;
  /* virtual */ double volume() const /* override */;
  /* virtual */ std::ostream& print(std::ostream&) const /* override */;

  bool intersect(Ray const&) const;
  bool intersect(Ray const& ray, float& dist) const;
  bool intersect(Ray const& ray, float& dist, std::shared_ptr<Shape> & ptr) const;
  bool intersect(Ray const& ray, float& dist, std::string& name) const;
  bool intersect_ptr(
    Ray const& ray,
    float& dist,
    std::shared_ptr<Shape> & ptr) const;
  glm::vec3 intersect_normal(Ray const& ray) const;
  std::unordered_map<std::string ,std::shared_ptr<Shape>> get_children();
  Raystructure raystruct_intersect(Ray const& r) const;

  void add(std::shared_ptr<Shape> const& shared_shape);
  void remove(std::string const& shape);

  void translate(glm::vec3 const&) override;

private:
  std::unordered_map<std::string, std::shared_ptr<Shape>> children_;
};

#endif
