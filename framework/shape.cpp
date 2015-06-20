#include "shape.hpp"

Shape::Shape() : color_{0.0, 0.0, 0.0}, name_{} {}
Shape::Shape(Color const& c, std::string const& n) : color_{c}, name_{n} {}

/* virtual */ std::ostream& Shape::print(std::ostream& os) const {
  //not implemented yet
  os << "\n" << "Shape \"" << name_ << "\" of color: " << color_;
  return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) { 
  s.print(os); 
}
