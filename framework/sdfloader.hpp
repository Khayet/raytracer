#ifndef SDFloader_HPP
#define SDFloader_HPP

#include "shape.hpp"
#include "material.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include <fstream>
#include <map>
#include <iostream>
#include <string>



class SDFloader
{
  public:
    void load(std::string const&);

  private:
    std::map<std::string, Material> materials_;

};

#endif
