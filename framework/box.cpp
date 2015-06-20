#include "box.hpp"

Box::Box() : 
    Shape{},
    min_{glm::vec3{0.0, 0.0, 0.0}},
    max_{glm::vec3{0.0, 0.0, 0.0}} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) : 
    Shape{}, min_{min}, max_{max} {}

Box::Box(Color const& clr, std::string const& n,
    glm::vec3 const& min, glm::vec3 const& max) :
    Shape{clr, n}, min_{min}, max_{max} {}

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