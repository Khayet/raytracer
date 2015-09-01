#ifndef RAY_T_HPP
#define RAY_T_HPP

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

// A Ray transformed by a glm::mat4 transformation matrix.

struct Ray_T 
{
  Ray_T(glm::vec4 orig, glm::vec4 dir) : origin{orig}, direction{dir} {}
  
  void transform(glm::mat4 const& matrix) {
    origin = origin * matrix;
    direction = direction * matrix;
  }
  
  glm::vec4 origin;
  glm::vec4 direction;
};

#endif
