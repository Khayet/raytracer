#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>

struct Light {
  std::string name;
  glm::vec3 position;
  float intensity_amb;
  float intensity_dif;
};

#endif 
