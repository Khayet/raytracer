// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "box.hpp"
#include "color.hpp"
#include "composite.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "ray.hpp"
#include "raystructure.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include <limits>
#include <math.h>
#include <string>
#include <glm/glm.hpp>

class Renderer
{
public:
  Renderer();
  Renderer(unsigned w, unsigned h, std::string const& file);
  Renderer(Renderer const& copy_renderer);
  void render();
  void render(Scene const& render_scene);
  void write(Pixel const& p);
  Ray shootRay(int x, int y, Scene const& render_scene);
  Color shade(std::shared_ptr<Shape> const& shape_ptr, Scene const& scene, Material const& material, Raystructure const& raystructure_);  
  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }
	unsigned width();
	unsigned height();
	
	
private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
