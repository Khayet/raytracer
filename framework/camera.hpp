#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

#include <string>

class Camera {
public:
	Camera(std::string name, double horFOV) 
			: name_{name}, horFOV_{horFOV} {
			}
private:
  std::string name_;
  //glm::vec3 position_; NOT NEEDED SEE SPECIFICATIONS EXERCISE07
  double horFOV_;
};

#endif
