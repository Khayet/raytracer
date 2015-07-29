#include "sdfloader.hpp"
#include "scene.hpp"
#include <regex>
#include <memory>
#include <vector>
#include <map>

void SDFloader::load(std::string const& filename) {
	//Scene read_scene;
	std::vector<std::shared_ptr<Shape>> shapes_;
  //std::ifstream file{"/home/moka3156/Dokumente/raytracer/framework/res/material_data.sdf"};
  std::ifstream file{filename};
  //file.open(filename, std::ifstream::in);
  if (!file) 
  {
    std::cout << "file not open \n";
  }
  std::string curr_line;
  while(std::getline(file, curr_line)) 
  {
    std::cout << curr_line << "\n";
    std::stringstream test(curr_line);
		std::string curr_word;
		while(test >> curr_word)
		{
			if (curr_word =="define")
			{
				std::cout << "Define what?"; 
				test >> curr_word;
			
				if (curr_word =="material")
				{
					std::cout << " MATERIAL "; //TEST
					test >> curr_word;
					std::string material_name = curr_word;
					double ka_f;
					test >> ka_f;
					double ka_s;
					test >> ka_s;
					double ka_t;
					test >> ka_t;				
					double kd_f;
					test >> kd_f;
					double kd_s;
					test >> kd_s;
					double kd_t;
					test >> kd_t;				
					double ks_f;
					test >> ks_f;
					double ks_s;
					test >> ks_s;
					double ks_t;
					test >> ks_t;									
					float exp_m;
					test >> exp_m;	
					
					Material temp_mat
						{material_name, Color{ka_f,ka_s,ka_t}, Color{kd_f,kd_s,kd_t},Color{ks_f,ks_s,ks_t}, exp_m};
					materials_.insert(std::make_pair(material_name,temp_mat));
					std::cout << "Habe "<< temp_mat.name()<< " erschaffen." << std::endl;
					auto shared_material = std::make_shared<Material>(Material
						{material_name, Color{ka_f,ka_s,ka_t}, Color{kd_f,kd_s,kd_t},Color{ks_f,ks_s,ks_t}, exp_m});
				}
					
				if (curr_word =="sphere"){
					std::cout << " SPHERE "; //TESTZEILE
					test >> curr_word;
					std::string sphere_name = curr_word;
					double center_x;
					test >> center_x;
					double center_y;
					test >> center_y;
					double center_z;
					test >> center_z;				
					double radius;
					test >> radius;		
					std::string sphmaterial_name;
					test >> sphmaterial_name;
	

					std::map<std::string, Material>::iterator it;
					it = materials_.find(sphmaterial_name);
					Sphere temp_sphere
						{it->second, sphere_name, glm::vec3{center_x,center_y,center_z},radius};
						std::cout << "Habe "<< temp_sphere.name()<< " erschaffen." << std::endl;//TESTZEILE
					auto shared_sphere = std::make_shared<Sphere>(Sphere
						{it->second, sphere_name, glm::vec3{center_x,center_y,center_z},radius});
					shapes_.push_back(shared_sphere);
				}
				
				if (curr_word =="box"){
					std::cout << " BOX "; //TESTZEILE
					test >> curr_word;
					std::string box_name = curr_word;
					double min_x;
					test >> min_x;
					double min_y;
					test >> min_y;
					double min_z;
					test >> min_z;
					double max_x;
					test >> max_x;
					double max_y;
					test >> max_y;
					double max_z;
					test >> max_z;						
					std::string boxmaterial_name;
					test >> boxmaterial_name;

					std::map<std::string, Material>::iterator it;
					it = materials_.find(boxmaterial_name);
					Box temp_box
						{it->second, box_name, glm::vec3{min_x, min_y, min_z}, 
																	 glm::vec3{max_x, max_y, max_z}};
						std::cout << "Habe "<< temp_box.name()<< " erschaffen." << std::endl;//TESTZEILE
					auto shared_box = std::make_shared<Box>(Box
						{it->second, box_name, glm::vec3{min_x, min_y, min_z}, 
																	 glm::vec3{max_x, max_y, max_z}});
					shapes_.push_back(shared_box); //push Pointer statt Box					
				}
			}
			if(curr_word== "#"){ //Kommentarzeile
			}
						
			std::cout << "Hello line! ('o')/ "<< std::endl; //TESTZEILE
		}
  // std::string name;
  // Color clr;
  // float highlight;
  }
}
