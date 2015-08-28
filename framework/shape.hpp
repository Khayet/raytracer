#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <ostream>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "raystructure.hpp"


class Shape {

public:
  Shape();
  Shape(Material const&, std::string const&);

  virtual ~Shape();

  Material material() const;
  std::string name() const;

  virtual double area() const = 0;
  virtual double volume() const = 0;
	
  virtual std::ostream& print(std::ostream&) const;
	virtual bool intersect(Ray const& ray, float& t) const = 0;
	virtual glm::vec3 intersect_normal(Raystructure const& raystructure) const = 0;
private:
  Material material_;
  std::string name_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif 
