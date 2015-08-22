// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

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
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Ray ray = shootRay(x, y, scene);
      float distance = 0.0;
//      std::cout<<scene.shapes_.size()<< std::endl;

      for (auto it : scene.shapes_) {
        bool test = false;
        test = it->intersect(ray, distance);
        //std::cout << x << ", " << y << std::endl;

        if (test && distance > 0) {
          std::cout << "DOES INTERSECT" << std::endl;
          Pixel p(x,y);
          p.color = Color(0.0, 1.0, 0);
          write(p);
        } else {
          std::cout << "n ";
          Pixel p(x,y);
          p.color = Color(0.5, 0.5, 0.5);
          write(p);
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

Ray Renderer::shootRay(int x, int y, Scene const& scene) {
  Ray shotRay{{0.0,0.0,0.0}, {0.0,0.0,-1.0}};
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
