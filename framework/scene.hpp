#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <map>
#include <memory>
#include "camera.hpp"
#include "composite.hpp"
#include "light.hpp"
#include "material.hpp"
#include "shape.hpp"


struct Scene {
	Scene(
	  std::map<std::string, Material> materials, 
	  std::vector<std::shared_ptr<Shape>> shapes, 
	  std::vector<Light> lights, 
	  std::shared_ptr<Composite> composite_ptr,
	  Camera camera) 
		: materials_{materials}, shapes_{shapes}, lights_{lights}, composite_ptr_{composite_ptr}, camera_{camera}{}
	Scene(Scene const& copy_template) 
		: materials_{copy_template.materials_}, 
		shapes_{copy_template.shapes_}, 
		lights_{copy_template.lights_}, 
		composite_ptr_{copy_template.composite_ptr_},
		camera_{copy_template.camera_}{}
	
	std::map<std::string, Material> materials_;
	std::vector<std::shared_ptr<Shape>> shapes_;
	std::vector<Light> lights_;
	std::shared_ptr<Composite> composite_ptr_;
	Camera camera_;
};

#endif
