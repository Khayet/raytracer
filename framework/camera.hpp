#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

#include <string>

class Camera {
public:

private:
  std::string name_;
  glm::vec3 position_;
  double horFOV_;
};

#endif