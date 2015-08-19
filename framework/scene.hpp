#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <map>
#include <memory>
#include "camera.hpp"
#include "shape.hpp"
#include "light.hpp"
#include "material.hpp"


struct Scene {
	Scene(std::map<std::string, Material> materials, std::vector<std::shared_ptr<Shape>> shapes, std::vector<Light>  lights, Camera camera) 
		: materials_{materials}, shapes_{shapes}, lights_{lights}, camera_{camera}{}
	Scene(Scene const& copy_template) 
		: materials_{copy_template.materials_}, shapes_{copy_template.shapes_}, 
		lights_{copy_template.lights_}, 
		camera_{copy_template.camera_}{}
	
	std::map<std::string, Material> materials_;
	std::vector<std::shared_ptr<Shape>> shapes_;
	std::vector<Light> lights_;
	Camera camera_;
};

#endif
