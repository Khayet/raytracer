#include "sdfloader.hpp"
#include "scene.hpp"
#include <sstream>
#include <memory>
#include <vector>
#include <map>

Scene SDFloader::load(std::string const& filename) {
  std::ifstream file{filename};
  std::vector<std::shared_ptr<Shape>> shapes;
	std::map<std::string, Material> materials;

	std::string out_rendcam_name;
	std::string out_file_name;
	unsigned out_x_res;
	unsigned out_y_res;

	std::string out_camera_name;
	double out_fov_x;
	bool read_camera = false;	//Test for correct declaration
	glm::vec3 out_eye_pos;
	glm::vec3 out_dir;
	glm::vec3 out_up;

  std::unordered_map<std::string,  std::shared_ptr<Shape>> composite_;
  std::unordered_map<std::string, std::shared_ptr<Shape>> map_children;

  std::string transform_name;
  std::string transform_kind;
  unsigned trans_x, trans_y, trans_z;

  std::vector<Light> lights_;
  if (!file) {
    std::cout << "file not open \n";
  }

  std::string curr_line;
  while (std::getline(file, curr_line)) {
    std::cout << curr_line << "\n";
    std::istringstream test(curr_line);
		std::string curr_word;

		while(test >> curr_word) {
			if (curr_word =="define")	{
				test >> curr_word;

				if (curr_word =="material")	{
					test >> curr_word;
					std::string material_name = curr_word;
					//float ka_f << test;
					float ka_f=0.0, ka_s=0.0, ka_t=0.0,	kd_f=0.0, kd_s=0.0, kd_t=0.0,	ks_f=0.0, ks_s=0.0, ks_t=0.0, exp_m=0.0;

					test >> ka_f >> ka_s >> ka_t
							 >> kd_f >> kd_s >> kd_t
							 >> ks_f >> ks_s >> ks_t
							 >> exp_m;

					Material temp_mat{material_name, Color{ka_f,ka_s,ka_t}, Color{kd_f,kd_s,kd_t}, Color{ks_f,ks_s,ks_t}, exp_m};

					materials.insert(std::make_pair(material_name,temp_mat));

					auto shared_material = std::make_shared<Material>(Material
						{material_name, Color{ka_f,ka_s,ka_t}, Color{kd_f,kd_s,kd_t}, Color{ks_f,ks_s,ks_t}, exp_m});
				}

				if (curr_word =="shape") {
					test >> curr_word;

					if (curr_word =="sphere") {
						test >> curr_word;
						std::string sphere_name = curr_word;

						double center_x=0.0, center_y=0.0, center_z=0.0, radius=0.0;
						test >> center_x >> center_y >> center_z;
						test >> radius;

						std::string sphmaterial_name;
						test >> sphmaterial_name;

						std::map<std::string, Material>::iterator it;
						it = materials.find(sphmaterial_name);
						Sphere temp_sphere{it->second, sphere_name, glm::vec3{center_x,center_y,center_z},radius};
						auto shared_sphere = std::make_shared<Sphere>(Sphere
							{it->second, sphere_name, glm::vec3{center_x,center_y,center_z},radius});
						shapes.push_back(shared_sphere);
						map_children.insert(std::make_pair(sphere_name, shared_sphere));
					}

					if (curr_word =="box") {
						test >> curr_word;
						std::string box_name = curr_word;
						double min_x=0.0, min_y=0.0, min_z=0.0, max_x=0.0, max_y=0.0, max_z=0.0;

						test >> min_x >> min_y >> min_z
								 >> max_x >> max_y >> max_z;

						std::string boxmaterial_name;
						test >> boxmaterial_name;

						std::map<std::string, Material>::iterator it;
						it = materials.find(boxmaterial_name);
						Box temp_box
							{it->second, box_name, glm::vec3{min_x, min_y, min_z},
																		 glm::vec3{max_x, max_y, max_z}};

						auto shared_box = std::make_shared<Box>(Box
							{it->second, box_name, glm::vec3{min_x, min_y, min_z},
																		 glm::vec3{max_x, max_y, max_z}});
						shapes.push_back(shared_box); //push pointer instead of Box
						map_children.insert(std::make_pair(box_name, shared_box));

					}

					if (curr_word =="composite") {
  					std::vector<std::string> parsed_children;
            std::unordered_map<std::string, std::shared_ptr<Shape>> copy_temp;

            std::string composite_name;
						test >> composite_name;

						std::string temp;
						test >> temp;
						std::string previous_string = temp;

						while (!temp.empty() && temp != previous_string) {
							previous_string = temp;
							parsed_children.push_back(temp);

						  test >> temp;
					  }

					  std::string shape_name;
					  for (auto const& it : parsed_children) {
              auto it_child = map_children.find((it));
              shape_name = it_child->second->name();
						  copy_temp.insert(std::make_pair(
						    it_child->second->name(),
						    it_child->second));
						}

		        Material temp_mat{"Composite", Color{0,0,0}, Color{0,0,0},Color{0,0,0}, 0};
						Composite temp_composite{temp_mat, composite_name, copy_temp};

						auto shared_composite = std::make_shared<Composite>(temp_composite);
						shapes.push_back(shared_composite);
						// Add to Componenten Database
            map_children.insert(std::make_pair(composite_name, shared_composite));
            composite_.insert(std::make_pair(composite_name, shared_composite));
					}
				}

				if(curr_word=="light") {
					test >> curr_word;
					std::string light_name = curr_word;

					double pos_x=0.0, pos_y=0.0, pos_z=0.0;
					test >> pos_x >> pos_y >> pos_z;

					float int_amb_r=0.0, int_amb_g=0.0, int_amb_b=0.0;
					float int_dif_r=0.0, int_dif_g=0.0, int_dif_b=0.0;

					test >> int_amb_r >> int_amb_g >> int_amb_b
							 >> int_dif_r >> int_dif_g >> int_dif_b;

					Light temp_light{light_name, glm::vec3{pos_x, pos_y, pos_z},
													Color{int_amb_r, int_amb_b, int_amb_g},
													Color{int_dif_r,int_dif_b,int_dif_g}};

					lights_.push_back(temp_light);
				}

				if(curr_word == "camera") {
					test >> curr_word;
					out_camera_name = curr_word;
					test >> out_fov_x
							 >> out_eye_pos.x >> out_eye_pos.y >> out_eye_pos.z
							 >> out_dir.x >> out_dir.y >> out_dir.z
							 >> out_up.x >> out_up.y >> out_up.z;

					read_camera = true;
				}
			}

			if (curr_word == "transform") {
				//test >> curr_word;
				test >> transform_name >> transform_kind >> trans_x >> trans_y >> trans_z;

				auto sh = map_children.find(transform_name);
				if ("translate" == transform_kind) {
					glm::vec3 v{trans_x, trans_y, trans_z};
					sh->second->translate(v);
				}
			}

			if(curr_word == "render") {

				test >> curr_word;
				out_rendcam_name = curr_word;
				test >> out_file_name;
				test >> out_x_res;
				test >> out_y_res;

				Camera cam(
		      out_camera_name,
		      out_fov_x,
		      out_eye_pos,
		      out_dir,
		      out_up);
		    Material root_mat
						{"Composite", Color{0,0,0}, Color{0,0,0},Color{0,0,0}, 0};
				Composite root{root_mat, "root", composite_, map_children};
				std::shared_ptr<Composite> shared_composite =
				    std::make_shared<Composite>(root);
				Renderer rend{out_x_res, out_y_res, out_file_name};
				rend.render(Scene(materials, shapes, lights_, shared_composite, cam));
			}
			if(curr_word== "#"){
			}
		}
  }

	if (read_camera) {
		Camera camera_scene(
      out_camera_name,
      out_fov_x,
      out_eye_pos,
      out_dir,
      out_up);
    Material root_mat
						{"Composite", Color{0,0,0}, Color{0,0,0},Color{0,0,0}, 0};
    Composite root{root_mat, "root", composite_, map_children};
		std::shared_ptr<Composite> shared_composite =
				    std::make_shared<Composite>(root);
		Scene read_scene{materials, shapes, lights_, shared_composite, camera_scene};
		return read_scene;
	}
	Material root_mat
						{"Composite", Color{0,0,0}, Color{0,0,0},Color{0,0,0}, 0};
  Composite root{root_mat, "root", composite_, map_children};
	std::shared_ptr<Composite> shared_composite =
				    std::make_shared<Composite>(root);
	Scene default_read{materials, shapes, lights_, shared_composite,
	  Camera("Default", 4.0, {0,0,0},{0,0,-1.0},{0,1.0,0})};
	return default_read;
}
