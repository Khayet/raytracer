#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"

class Box: public Shape {

public:
  glm::vec3 min() const {
    return min_;
  }

  glm::vec3 max() const {
    return max_;
  }

private:
  glm::vec3 min_;
  glm::vec3 max_;
};

#endif