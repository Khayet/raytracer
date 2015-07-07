#include "sdfloader.hpp"


void SDFloader::load(std::string const& filename) {
  //std::ifstream file{"/home/moka3156/Dokumente/raytracer/framework/res/material_data.sdf"};
  std::ifstream file{filename};
  //file.open(filename, std::ifstream::in);

  if (!file) {
    std::cout << "file not open \n";
  }

  std::string curr_line;
  std::getline(file, curr_line);
  std::cout << curr_line << "\n";
}