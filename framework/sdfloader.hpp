#ifndef SDFloader_HPP
#define SDFloader_HPP

#include "material.hpp"
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