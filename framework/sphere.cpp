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
  return Sphere::intersect(ray, dist);
}

bool Sphere::intersect(Ray const& ray, float& dist) const {
  glm::vec3 dir = glm::normalize(ray.direction);
  //std::cout<<"Do you even intersect? SPHERE"<< std::endl;
  return glm::intersectRaySphere(
      ray.origin, dir,
      center(), radius()*radius(),
      dist);

  //return result;
}

glm::vec3 Sphere::intersect_normal(Ray const& ray) const{
	float distance = 0;
	glm::vec3 temp = glm::normalize(ray.direction);
	bool intersect_test = intersect(ray, distance);
  glm::vec3 intersection ={ray.origin +glm::vec3{(distance * temp.x),
		(distance * temp.y),
		(distance * temp.z)}};  
  glm::vec3 normal = (intersection - center_);
  normal = glm::normalize(normal);
  return normal;
}

Raystructure Sphere::raystruct_intersect(Ray const& r) const {
  bool intersect_test = false;
  float distance = 0;
  intersect_test = intersect(r, distance);
  if (true == intersect_test){
    return Raystructure{r.origin, r.direction, Color{0,0,0}, 
		                  material(), distance,	intersect_normal(r)};
	}
	return Raystructure{r.origin, r.direction, Color{0,0,0}, 
		                  material(), std::numeric_limits<float>::max(),	
		                  glm::vec3{0, 0, 0}};
}
