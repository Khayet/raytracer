#include "sdfloader.hpp"
#include <regex>

void SDFloader::load(std::string const& filename) {
  //std::ifstream file{"/home/moka3156/Dokumente/raytracer/framework/res/material_data.sdf"};
  std::ifstream file{filename};
  //file.open(filename, std::ifstream::in);
  if (!file) {
    std::cout << "file not open \n";
  }
  std::string curr_line;
  while(std::getline(file, curr_line)) {
    std::cout << curr_line << "\n";

// "define\s{1}material\s{1}\w+\s{1}\d+\s{1}\d+\s{1}\d+\s{1}\d+\s{1}\d+\s{1}\d+\"

//define\s* material
        

  // std::string name;
  // Color clr;
  // float highlight;


  }
}