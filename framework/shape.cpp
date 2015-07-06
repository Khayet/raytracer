#include "shape.hpp"

Shape::Shape() : material_{Material{}}, name_{} {
  std::cout << "ctor Shape ()" << "\n";
}
Shape::Shape(Material const& material, std::string const& n) : material_{material}, name_{n} {
  std::cout << "ctor Shape (material, string)" << "\n";
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


/* virtual */ std::ostream& Shape::print(std::ostream& os) const {
  //not implemented yet
  os << "\n" << "Shape \"" << name_ << "\" of material: " <<material_;
  return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) { 
  return s.print(os); 
  
}
