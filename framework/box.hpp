#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <cmath>

class Box: public Shape {

public:
  Box() : 
    Shape{}, 
    min_{glm::vec3{0.0, 0.0, 0.0}}, 
    max_{glm::vec3{0.0, 0.0, 0.0}} {}

  Box(glm::vec3 const& min, glm::vec3 const& max) : 
    Shape{}, min_{min}, max_{max} {}

  Box(Color const& clr, std::string const& n,
    glm::vec3 const& min, glm::vec3 const& max) :
    Shape{clr, n}, min_{min}, max_{max} {}

  glm::vec3 min() const { return min_; }
  glm::vec3 max() const { return max_; }

  /* virtual */ double area() const override {
    // 6*(area of one side)
    return 6.0 * (std::abs(max_.x - min_.x) * std::abs(max_.x - min_.x));
  }

  /* virtual */ double volume() const override {
    //length * width * height
    return std::abs(max_.x - min_.x) 
      * std::abs(max_.y - min_.y) 
      * std::abs(max_.z - min_.z);
  }

private:
  glm::vec3 min_;
  glm::vec3 max_;
};

#endif