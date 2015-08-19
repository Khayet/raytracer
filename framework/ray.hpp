#ifndef RAY_HPP
#define RAY_HPP

#include "glm/vec3.hpp"

struct Ray
{
	Ray(glm::vec3 orig,glm::vec3 direct): origin{orig}, direction{direct}{}
  glm::vec3 origin;
  glm::vec3 direction;
};

#endif
