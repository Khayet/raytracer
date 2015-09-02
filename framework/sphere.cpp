#include "sphere.hpp"
//
Sphere::Sphere() : Shape{}, center_{glm::vec3{0.0, 0.0, 0.0}}, radius_{0.0} {
  std::cout << "ctor sphere ()" << "\n";
  }  
Sphere::Sphere(glm::vec3 const& c, double r) : 
  Shape{}, center_{c}, radius_{r} {
    std::cout << "ctor sphere (center, radius)" << "\n";
  }

Sphere::Sphere(Material const& material, std::string const& n, glm::vec3 const& c, double r) :
    Shape{material, n}, center_{c}, radius_{r} {
      std::cout << "ctor sphere (material, name, center, radius)" << "\n";
    }

Sphere::Sphere(glm::vec3 const& c, double r, Material const& material, std::string const& n) :
    Shape{material, n}, center_{c}, radius_{r} {
      std::cout << "ctor sphere (center, radius, material, name)" << "\n";
    }

Sphere::~Sphere() { std::cout << "Sphere::~Sphere" << "\n"; }

/* virtual */ double Sphere::area() const {
  return 4.0 * PI * (radius_ * radius_);
}

/* virtual */ double Sphere::volume() const {
  return 4.0/3.0 * PI * (radius_ * radius_ * radius_);
}

/* virtual */ std::ostream& Sphere::print(std::ostream& os) const {
  os << "\n";
  os << "Sphere \"" << name() << "\" : \n";
  os << "  name    :  " << name() << "\n";
  os << "  material   :  " << material();

  os << "  center  :  "
    << "(" << center().x << "," << center().y << "," 
    << center().z << ")" << "\n"; 

  os << "  radius  :  " << radius() << "\n";
  os << "  area    :  " << area() << "\n";
  os << "  volume  :  " << volume() << "\n";

  return os;
}
bool Sphere::intersect(
    Ray const& ray, 
    float& dist, 
    std::shared_ptr<Shape> & ptr) const{
  return intersect(ray, dist);
}

bool Sphere::intersect(Ray const& ray, float& dist) const {
/*
  Ray_T r = ray.transform(world_transformation_inv());
  auto orig = glm::vec3(r.origin);
  auto dir = glm::normalize(glm::vec3(r.direction));
*/
  return glm::intersectRaySphere(
    ray.origin, glm::normalize(ray.direction),
    center(), radius()*radius(),
    dist);
}

glm::vec3 Sphere::intersect_normal(Ray const& ray) const{
	float distance = 0;
	glm::vec3 dir = glm::normalize(ray.direction);
	bool intersect_test = intersect(ray, distance);
  glm::vec3 intersection = ray.origin + (distance * dir);  
  return glm::normalize(intersection - center_);
}

Raystructure Sphere::raystruct_intersect(Ray const& r) const {
  Raystructure returner{r.origin, r.direction, Color{0,0,0}, 
		                  material(), std::numeric_limits<float>::max(),	
		                  glm::vec3{0, 0, 0},false, nullptr};
  bool intersect_test = false;
  float distance = 0;
  intersect_test = intersect(r, distance);
  if (intersect_test) {
    returner.origin_ = r.origin;
    returner.direction_ = r.direction;
    returner.curr_color_ = Color{0,0,0};
    returner.material_ = material();
    returner.distance_ = distance;
    returner.normal_ = intersect_normal(r); 
    returner.is_hit_= intersect_test;
    returner.shape_ptr_ = std::make_shared<Sphere>(*this);
	}
	return returner;
}

void Sphere::translate(glm::vec3 const& t_vec) {
  glm::mat4 t_mat{1.0};
  t_mat[3] = glm::vec4(t_vec, 1); //create correct transformation matrix

  set_matrix(t_mat);
}
