#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "camera.hpp"
#include "light.hpp"

struct Scene {
	std::vector<Shape> shapes;
	std::vector<Light> lights;
	Camera camera;
};

#endif