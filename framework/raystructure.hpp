#ifndef BUW_RAYSTRUCTURE_HPP
#define BUW_RAYSTRUCTURE_HPP

#include "ray.hpp"
#include "color.hpp"

struct Raystructure{
	Raystructure (glm::vec3 const& origin, glm::vec3 const& direction, Color const& curr_color, 
	double distance, int ray_depth) 
	  : origin_{origin}, direction_{direction}, 
	intersection_{(distance * direction.x), (distance * direction.y),(distance * direction.z)}, 
	eye_ray_{origin, direction}, curr_color_{curr_color}, distance_{distance}, ray_depth_{ray_depth}{}

  glm::vec3 origin_;
  glm::vec3 direction_;
  glm::vec3 intersection_;
	Ray eye_ray_;
  Color curr_color_;
	double distance_;
  int ray_depth_;
};
#endif
