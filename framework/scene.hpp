#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <map>
#include <memory>
#include "camera.hpp"
#include "light.hpp"
#include "renderer.hpp"

struct Scene {
	Scene(std::map<std::string, Material> materials, std::vector<std::shared_ptr<Shape>> shapes, std::vector<Light>  lights, Renderer renderer, Camera camera) 
		: materials_{materials}, shapes_{shapes}, lights_{lights}, renderer_{renderer}, camera_{camera}{}
	Scene(Scene const& copy_template) 
		: materials_{copy_template.materials_}, shapes_{shapes_}, 
		lights_{copy_template.lights_}, renderer_{copy_template.renderer_}, 
		camera_{copy_template.camera_}{}
	
	std::map<std::string, Material> materials_;
	std::vector<std::shared_ptr<Shape>> shapes_;
	std::vector<Light> lights_;
	Renderer renderer_;
	Camera camera_;
};

#endif
