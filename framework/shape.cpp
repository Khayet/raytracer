#include "shape.hpp"
//
Shape::Shape() : material_{Material{}}, name_{}, 
  world_transformation_{1.0}, world_transformation_inv_{glm::inverse(world_transformation_)} {
  std::cout << "ctor Shape ()" << "\n";
}
Shape::Shape(Material const& material, std::string const& n) : material_{material}, name_{n}, 
  world_transformation_{1.0}, world_transformation_inv_{glm::inverse(world_transformation_)} {
}

/* virtual */ Shape::~Shape() {
  std::cout << "Shape::~Shape" << "\n";
}

/* virtual */std::string Shape::name() const{
  return name_;
}

/* virtual */Material Shape::material() const{
  return material_;
}

glm::mat4 Shape::set_matrix(glm::mat4 const& mat) { 
  world_transformation_ = mat;
  world_transformation_inv_ = glm::inverse(mat);
}

/* virtual */ std::ostream& Shape::print(std::ostream& os) const {
  //not implemented yet
  os << "\n" << "Shape \"" << name_ << "\" of material: " <<material_;
  return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) { 
  return s.print(os); 
  
}
