#ifndef BUW_RAYSTRUCTURE_HPP
#define BUW_RAYSTRUCTURE_HPP

#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "shape.hpp"

struct Raystructure{
  Raystructure() 
  : eye_ray_{glm::vec3{0.0,0.0,0.0}, glm::vec3{0.0,0.0,0.0}}, 
		curr_color_{Color{0.0,0.0,0.0}}, 
		material_{
			Material{Color{0.0,0.0,0.0},
				       Color{0.0,0.0,0.0}, 
				       Color{0.0,0.0,0.0}}}{}
			
	Raystructure (
	  glm::vec3 const& origin, 
	  glm::vec3 const& direction, 
	  Color const& curr_color, 
	  Material const& material,
	  double distance, 
	  glm::vec3 const& normal,
	  bool is_hit) 
	  : origin_{origin}, direction_{direction}, 
	intersection_{(distance * direction.x), (distance * direction.y),(distance * direction.z)}, 
	eye_ray_{origin, direction}, curr_color_{curr_color}, material_{material}, distance_{distance},  
	  normal_{normal},
	  is_hit_{is_hit}{}
	Raystructure (Raystructure const& copy_raystruct) 
	  : origin_{copy_raystruct.origin_}, 
	  direction_{copy_raystruct.direction_}, 
	  intersection_{copy_raystruct.intersection_}, 
	  eye_ray_{copy_raystruct.origin_, copy_raystruct.direction_}, 
    curr_color_{copy_raystruct.curr_color_}, 
    material_{copy_raystruct.material_},
    distance_{copy_raystruct.distance_},  
	  normal_{copy_raystruct.normal_},
	  is_hit_{copy_raystruct.is_hit_}
	  {}

  glm::vec3 origin_;
  glm::vec3 direction_;
  glm::vec3 intersection_;
	Ray eye_ray_;
  Color curr_color_;
  Material material_;
	double distance_;
  glm::vec3 normal_;
  bool is_hit_;
};
#endif
