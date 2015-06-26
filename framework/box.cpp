#include "box.hpp"

Box::Box() : 
    Shape{},
    min_{glm::vec3{0.0, 0.0, 0.0}},
    max_{glm::vec3{0.0, 0.0, 0.0}} { std::cout << "ctor box ()" << "\n"; }

Box::Box(glm::vec3 const& min, glm::vec3 const& max) : 
    Shape{}, min_{min}, max_{max} { std::cout << "ctor box (min, max)" << "\n"; }

Box::Box(Color const& clr, std::string const& n,
    glm::vec3 const& min, glm::vec3 const& max) :
    Shape{clr, n}, min_{min}, max_{max} {
      std::cout << "ctor box (color, name, min, max)" << "\n";
    }

Box::~Box() { std::cout << "Box::~Box" << "\n"; }

/* virtual */ double Box::area() const {
    // 6*(area of one side)
    return 6.0 * (std::abs(max_.x - min_.x) * std::abs(max_.x - min_.x));
}

/* virtual */ double Box::volume() const {
  //length * width * height
  return std::abs(max_.x - min_.x) 
    * std::abs(max_.y - min_.y) 
    * std::abs(max_.z - min_.z);
}

/* virtual */ std::ostream& Box::print(std::ostream& os) const {
  os << "\n";
  os << "Box \"" << name() << "\" : \n";
  os << "  name    :  " << name() << "\n";
  os << "  color   :  " << color();

  os << "  minimum :  " 
    << "(" << min().x << "," << min().y << "," << min().z << ")" << "\n";
  
  os << "  maximum :  "
    << "(" << max().x << "," << max().y << "," << max().z << ")" << "\n";
      
  os << "  area    :  " << area() << "\n";
  os << "  volume  :  " << volume() << "\n";

  return os;
}

std::ostream& operator<<(std::ostream& os, Box const& b) {
  b.print(os);
}
