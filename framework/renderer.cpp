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

void Renderer::render() {
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

void Renderer::render(Scene const& scene) {
  int ray_depth = 3;                      //Tiefe der Strahlen
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      float distance = 0.0;
      float min_distance = std::numeric_limits<float>::max();
			Ray pixel_ray = shootRay(x, y, scene);

      bool pixel_drawn = false;
      for(auto it : scene.shapes_) {
				bool test = false;

        test = it->intersect(pixel_ray, distance);
        std::cout << x << ", " << y << std::endl;
        
        if (test && distance > 0 && min_distance > distance) {          
          pixel_drawn = true;
          min_distance = distance;
          Raystructure intersec_struct(pixel_ray.origin, pixel_ray.direction, 
            (*it).material().color_ka(), distance, ray_depth);
          std::cout<<"DOES INTERSECT "<< std::endl;
					Pixel p(x,y);
          p.color = shade(it, scene, (*it).material(), intersec_struct);
					write(p);
				} else {
          if (false == pixel_drawn) {
						std::cout << pixel_ray.direction.x << " " << pixel_ray.direction.y << " " << pixel_ray.direction.z << std::endl;
            std::cout<<"NO " << std::endl;
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

void Renderer::write(Pixel const& p) {
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

Color Renderer::shade (
  std::shared_ptr<Shape> const& shape_ptr, 
  Scene const& scene, 
  Material const& material, 
  Raystructure const& raystructure) {
    
  Color shade_color = {0.0,0.0,0.0};
  shade_color = material.color_kd();
  if (scene.lights_.empty()) {
    return shade_color;
  } else {
    Color diffuse = {0.0,0.0,0.0};
    Color specular = {0.0,0.0,0.0};
    Color ambient = {0.0,0.0,0.0};

    for (int i = 0; i < scene.lights_.size(); ++i) {      

      //sum up ambient light:
      ambient.r += scene.lights_[i].intensity_amb_.r;
      ambient.g += scene.lights_[i].intensity_amb_.g;
      ambient.b += scene.lights_[i].intensity_amb_.b;  
   
      /**
        DIFFUSE LIGHTING
        modeled after Lambert's law
fuse_intensity = 
            (dot product of surface normal and incident vector) 
          * (brightness of light source)
          * (diffuse coefficient of material)
      */
      //respects calculation error, if intersection lies within Shape
      glm::vec3 light_orig = { 
        (raystructure.intersection_.x + 
          (scene.lights_[i].position_ - raystructure.intersection_).x*0.001),
        (raystructure.intersection_.y + 
          (scene.lights_[i].position_ - raystructure.intersection_).y*0.001),
        (raystructure.intersection_.z + 
          (scene.lights_[i].position_ - raystructure.intersection_).z*0.001)};

      Ray light_ray = {light_orig,
        (glm::normalize(scene.lights_[i].position_ - raystructure.intersection_))}; 

      glm::vec3 normal = shape_ptr->intersect_normal(raystructure);
      glm::normalize(normal);
      
      float dotProd_dif = glm::dot(light_ray.direction, normal);
 
      diffuse.r += scene.lights_[i].intensity_dif_.r * dotProd_dif*material.color_kd().r;
      diffuse.g += scene.lights_[i].intensity_dif_.g * dotProd_dif*material.color_kd().g;
      diffuse.b += scene.lights_[i].intensity_dif_.b * dotProd_dif*material.color_kd().b;
   
      diffuse.r = std::fmax(0.0, std::fmin(1.0, diffuse.r));
      diffuse.g = std::fmax(0.0, std::fmin(1.0, diffuse.g));
      diffuse.b = std::fmax(0.0, std::fmin(1.0, diffuse.b));




      /**
        SPECULAR LIGHTING
        diffuse_intensity = 
            (dot product of normalized reflection and spectator vector) 
          ^ (specular coefficient of material)
      */
/*
      glm::vec3 reflection = shape_ptr->intersect_normal(raystructure) + light_ray.direction;     
      reflection = {(reflection.x * (-1)), (reflection.y * (-1)), (reflection.z * (-1))};
      reflection = glm::normalize(reflection);
*/

      float dot_temp = glm::dot(normal, glm::normalize(scene.lights_[i].position_ - raystructure.intersection_));
      glm::vec3 minuend = 
        {(2 * dot_temp * normal.x), (2 * dot_temp * normal.y),(2 * dot_temp * normal.z)};
      glm::vec3 reflection = minuend - glm::normalize(raystructure.intersection_ - scene.lights_[i].position_);
      reflection = glm::normalize(reflection);


      glm::vec3 eyeray_direction = glm::normalize(raystructure.intersection_-scene.camera_.position());
      float dotProd_spec = glm::dot(reflection, eyeray_direction);
      
      /* DEBUG
      std::cout << "Reflection: " << reflection.x << " "
      << reflection.y <<" "<< reflection.z << " " << std::endl;
      std::cout << "Eyeray: "<< eyeray_direction.x << " " << eyeray_direction.y 
      << " " << eyeray_direction.z << " " << std::endl;
      std::cout << "DOTProduct_spec: " << dotProd_spec << std::endl;
      std::cout << "Normal: " << normal.x << " "
      << normal.y <<" "<< normal.z << " " << std::endl;      
      std::cout << "DOTProductTemp: " << dot_temp << std::endl;
      */
      
      specular.r += scene.lights_[i].intensity_dif_.r * material.color_ks().r * pow(dotProd_spec, material.m());
      specular.g += scene.lights_[i].intensity_dif_.g * material.color_ks().g * pow(dotProd_spec, material.m());
      specular.b += scene.lights_[i].intensity_dif_.b * material.color_ks().b * pow(dotProd_spec, material.m());

      specular.r = std::fmax(0.0, std::fmin(1.0, specular.r));
      specular.g = std::fmax(0.0, std::fmin(1.0, specular.g));
      specular.b = std::fmax(0.0, std::fmin(1.0, specular.b));


    }
    
    ambient.r = std::fmax(0.0, std::fmin(1.0, material.color_ka().r * ambient.r));
    ambient.g = std::fmax(0.0, std::fmin(1.0, material.color_ka().g * ambient.g));
    ambient.b = std::fmax(0.0, std::fmin(1.0, material.color_ka().b * ambient.b));

    //only apply coefficient once, since it's the same material:
    diffuse *= material.color_kd(); 
    std::cout << "diff: " << diffuse << "spec: " << specular << "amb: " << ambient;
    shade_color = diffuse + specular + ambient;

    //std::cout << "(" << shade_color.r << ", " << shade_color.g << ", " << shade_color.b << ")" << "\n";

    return shade_color;
  }
}

Ray Renderer::shootRay(int x, int y, Scene const& scene)	{
/*	Ray shotRay{{0.0,0.0,0.0}, {0.0,0.0,-1.0}};
  double aspect_ratio = x/y;
  double p_width = 0.1;
  double screen_x = p_width * x;
  double screen_y = screen_x * aspect_ratio;
  
  tan(scene.camera_.camera.horFOV()/2);
  
  aspect_ratio * 
*/
  glm::vec3 position = scene.camera_.position();
  glm::vec3 direction = glm::normalize(scene.camera_.direction());
  glm::vec3 up = glm::normalize(scene.camera_.up());
  double fov_hor = scene.camera_.horFOV();
  double aspect_ratio = width_/height_;
  double fov_ver = aspect_ratio * fov_hor;

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
  	 std::cout << direc_shot.x << " " << direc_shot.y << " " << direc_shot.z << std::endl;
  direc_shot = glm::normalize(direc_shot);
	   std::cout << direc_shot.x << " " << direc_shot.y << " " << direc_shot.z << std::endl;
  return Ray(position, direc_shot);		

}

unsigned Renderer::width(){
  return width_;
}
unsigned Renderer::height(){
  return height_;
}
