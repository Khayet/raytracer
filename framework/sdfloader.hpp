#ifndef SDFloader_HPP
#define SDFloader_HPP
//
#include "box.hpp"
#include "composite.hpp"
#include "material.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include <fstream>
#include <map>
#include <unordered_map>
#include <iostream>
#include <string>


class SDFloader
{
  public:
    Scene load(std::string const&);
  private:
};

#endif
