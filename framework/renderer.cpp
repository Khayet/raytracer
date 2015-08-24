// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include <cmath>
#include "renderer.hpp"
Renderer::Renderer()
  : width_(0)
  , height_(0)
  , colorbuffer_(0, Color(0.0, 0.0, 0.0))
  , filename_("NULL")
  , ppm_(0, 0){}
Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}
Renderer::Renderer(Renderer const& copy_renderer)
  : width_(copy_renderer.width_)
  , height_(copy_renderer.height_)
  , colorbuffer_(copy_renderer.width_*copy_renderer.height_, 
  Color(0.0, 0.0, 0.0))
  , filename_(copy_renderer.filename_)
  , ppm_(copy_renderer.width_, copy_renderer.height_)
{}

void Renderer::render()
{
  const std::size_t checkersize = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
void Renderer::render(Scene const& scene)
{
  int ray_depth = 3;                      //Tiefe der Strahlen
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      float distance = 0.0;
      float min_distance = std::numeric_limits<float>::max();
			Ray pixel_ray = shootRay(x, y, scene);
//      std::cout<<scene.shapes_.size()<< std::endl;
      for(auto iterator:scene.shapes_) {

				bool test = false;
        bool pixel_drawn = false;
        test = (*iterator).intersect(pixel_ray, distance);
        std::cout << x << ", " << y << std::endl;
        if (true == test && 0 < distance && min_distance > distance) {          
          pixel_drawn = true;
          min_distance = distance;
          Raystructure intersec_struct(pixel_ray.origin, pixel_ray.direction,  (*iterator).material().color_ka(), 
          distance, ray_depth);
          std::cout<<"DOES INTERSECT"<< std::endl;
					Pixel p(x,y);
          p.color = shade(iterator, scene, (*iterator).material(), intersec_struct);
					write(p);
				}else {
          if (pixel_drawn = false){
          std::cout<<"n ";
          Pixel p(x,y);
          p.color = Color(0.5, 0.5, 0.5);
          write(p);
         }
			  }
		  }
    }
  }
  ppm_.save(filename_);
}
Color Renderer::shade(
  std::shared_ptr<Shape> const& shape_ptr, 
  Scene const& scene, 
  Material const& material, 
  Raystructure const& raystructure) {
    
  Color shade_color = {0.0,0.0,0.0};
  shade_color = material.color_kd();
  if(scene.lights_.empty()){
    return shade_color;
  }else{
      float ambient_r = 0;
      float ambient_g = 0;
      float ambient_b = 0;
    for ( int i = 0; i < scene.lights_.size(); ++i) {      
      ambient_r = scene.lights_[i].intensity_amb_.r + ambient_r;
      ambient_g = scene.lights_[i].intensity_amb_.g + ambient_g;
      ambient_b = scene.lights_[i].intensity_amb_.b + ambient_b;  
   
      glm::vec3 light_orig = { // Beachtet Berechnungsfehler, falls Schnittstelle  in der Form ist
        (raystructure.intersection_.x + 
          (scene.lights_[i].position_- raystructure.intersection_).x*0.001),
        (raystructure.intersection_.y + 
          (scene.lights_[i].position_- raystructure.intersection_).y*0.001),
        (raystructure.intersection_.z + 
          (scene.lights_[i].position_- raystructure.intersection_).z*0.001)};
      Ray light_ray = {light_orig,(glm::normalize(scene.lights_[i].position_- raystructure.intersection_))}; 
      glm::vec3 normal = shape_ptr->intersect_normal(raystructure.intersection_);
      float incident_light = scene.lights_[i].intensity_dif_.r  ;//HIERWEITERARBEITEN
      float diffuse_r = scene.lights_[i].intensity_dif_.r * material.color_kd().r;
      float diffuse_g = scene.lights_[i].intensity_dif_.g * material.color_kd().g;
      float diffuse_b = scene.lights_[i].intensity_dif_.b * material.color_kd().b;
     
      Color diffuse = material.color_kd();
      Color specular = material.color_ks();

    }
    ambient_r = material.color_ka().r * ambient_r;
    ambient_b = material.color_ka().b * ambient_g;
    ambient_g = material.color_ka().g * ambient_b;
    Color ambient = {ambient_r, ambient_g, ambient_b};  
    shade_color = material.color_ka();
    return shade_color;
  }
}

Ray Renderer::shootRay(int x, int y, Scene const& scene)	{
	Ray shotRay{{0.0,0.0,0.0}, {0.0,0.0,-1.0}};
/*  double aspect_ratio = x/y;
  double p_width = 0.1;
  double screen_x = p_width * x;
  double screen_y = screen_x * aspect_ratio;
  
  tan(scene.camera_.camera.horFOV()/2);
  
  aspect_ratio * 
*/
  glm::vec3 position = scene.camera_.position();
  glm::vec3 direction = scene.camera_.direction();
  glm::vec3 up = scene.camera_.up();
  glm::vec3 cam_v = {
    direction.y * up.z - up.y * direction.z,
    direction.z * up.x - up.z * direction.x,
    direction.x * up.y - up.y * direction.x,
    };
  up = {
    cam_v.y * direction.z - direction.y * cam_v.z,
    cam_v.z * direction.x - direction.z * cam_v.x,
    cam_v.x * direction.y - direction.y * cam_v.x,
    };
	float x_coordinate = width_;
	float y_coordinate = height_;

	float normalized_i = (x / x_coordinate) - 0.5;
  float normalized_j = (y / y_coordinate) - 0.5;
  glm::vec3 image_point = (normalized_i * cam_v) + 
                          (normalized_j * up) +
                          position + direction; 
  glm::vec3 direc_shot = image_point - position;
	return Ray(position, direc_shot);		
}

unsigned Renderer::width(){
  return width_;
}
unsigned Renderer::height(){
  return height_;
}
