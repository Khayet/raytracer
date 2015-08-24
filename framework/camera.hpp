#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

#include <string>

class Camera {
public:
  Camera(
  std::string name, 
  double horFOV, 
  glm::vec3 position, 
  glm::vec3 direction,
  glm::vec3 up) 
    : name_{name}, horFOV_{horFOV}, position_{position}, direction_{direction}, up_{up} {}
  std::string name() const {
		return name_;
  }  
  double horFOV() const { 
    return horFOV_;
  }
	glm::vec3 position() const {
	  return position_;
	}
  glm::vec3 direction() const { 
    return direction_;
  }
  glm::vec3 up() const { 
    return up_;
  }
private:
  std::string name_;
  double horFOV_;
  glm::vec3 position_; 
  glm::vec3 direction_;
  glm::vec3 up_;  
};

#endif
