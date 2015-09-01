#ifndef LIGHT_HPP
#define LIGHT_HPP
//
#include <string>
#include "color.hpp"

struct Light {
	Light(std::string light_name, glm::vec3 position, Color  int_amb, Color  int_dif) 
		: name_{light_name}, position_{position}, intensity_amb_{int_amb}, intensity_dif_{int_dif}{}
  std::string name_;
  glm::vec3 position_;
  Color intensity_amb_;
  Color intensity_dif_;
};

#endif 
