#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <algorithm>
#include <cmath>
#include <memory>
#include "../framework/shape.hpp"
#include "raystructure.hpp"

class Triangle: public Shape {
public:
  Triangle();
  Triangle(
    glm::vec3 const& avertex, 
    glm::vec3 const& bvertex, 
    glm::vec3 const& cvertex);
  Triangle(Material const& material, std::string const& n,
    glm::vec3 const& avertex, 
    glm::vec3 const& bvertex, 
    glm::vec3 const& cvertex);
  ~Triangle();

  glm::vec3 avertex() const { return avertex_; }
  glm::vec3 bvertex() const { return bvertex_; }
  glm::vec3 cvertex() const { return cvertex_; }
 
  /* virtual */ double area() const /* override */;
  /* virtual */ double volume() const /* override */;

  /* virtual */ std::ostream& print(std::ostream&) const /* override */;

  bool intersect(Ray const&) const;
  bool intersect(Ray const&, float& dist) const;
  bool intersect(
    Ray const& ray, 
    float& dist, 
    std::shared_ptr<Shape> & ptr) const;
  glm::vec3 intersect_normal(Ray const& ray) const;
  Raystructure raystruct_intersect(Ray const& r) const;
  
  void translate(glm::vec3 const&); 
 /* virtual void scale(double) override;
  virtual void rotate(double) override;
  virtual void rotate(glm::vec3 const&) override;
  */
private:
  glm::vec3 avertex_;
  glm::vec3 bvertex_;
  glm::vec3 cvertex_;
};

#endif

