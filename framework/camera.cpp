#include "camera.hpp"

Ray Camera::shoot_ray(unsigned x, unsigned y, unsigned width, unsigned height) const {
  double fov_hor = horFOV_ * (M_PI/180); //radians!
  double ratio = static_cast<double>(width)
                /static_cast<double>(height);
  double ratio_inv = static_cast<double>(height)
                    /static_cast<double>(width);
  double fov_ver = ratio * fov_hor; //radians!

  //cross product of dir and up:
  glm::vec3 right =
   { (direction_.y*up_.z - direction_.z*up_.y),
      (direction_.z*up_.x - direction_.x*up_.z),
      (direction_.x*up_.y - direction_.y*up_.z)
   };

  glm::normalize(right);

  float dist = 0.5 / std::tan(0.5*fov_hor);
  glm::vec3 dist_vec = direction_ * dist;

  float x_pos = static_cast<float>(x) / static_cast<float>(width) -0.5;
  float y_pos = ratio_inv * (static_cast<float>(y) / static_cast<float>(height)) -0.5;
  glm::vec3 pos_on_plane = right*x_pos + up_*y_pos;

  glm::vec3 image_point = position_ + dist_vec + pos_on_plane;
  glm::vec3 direc_shot = glm::normalize(image_point - position_);

  return Ray(position_, direc_shot);

}
