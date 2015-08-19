#ifndef SDFloader_HPP
#define SDFloader_HPP

#include "shape.hpp"
#include "scene.hpp"
#include "material.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "renderer.hpp"
#include <fstream>
#include <map>
#include <iostream>
#include <string>


class SDFloader
{
  public:
    Scene load(std::string const&);
		Renderer renderer_;
  private:

		

};

#endif
