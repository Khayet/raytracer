#ifndef RAY_HPP
#define RAY_HPP
//
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

#include "ray_T.hpp"

struct Ray
{
	Ray(glm::vec3 orig,glm::vec3 direct): origin{orig}, direction{direct}{}
  
  Ray_T transform(glm::mat4 const& matrix) const {
    Ray_T r{ glm::vec4(origin, 1), glm::vec4(direction,0) };

    r.origin = r.origin * matrix;
    r.direction = r.direction * matrix;

    return r;
  }
  
  glm::vec3 origin;
  glm::vec3 direction;
};

#endif
