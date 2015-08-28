#include "box.hpp"


Box::Box() : 
    Shape{},
    min_{glm::vec3{0.0, 0.0, 0.0}},
    max_{glm::vec3{0.0, 0.0, 0.0}} { std::cout << "ctor box ()" << "\n"; }

Box::Box(glm::vec3 const& min, glm::vec3 const& max) : 
    Shape{}, min_{min}, max_{max} { std::cout << "ctor box (min, max)" << "\n"; }

Box::Box(Material const& material, std::string const& n,
    glm::vec3 const& min, glm::vec3 const& max) :
    Shape{material, n}, min_{min}, max_{max} {
      std::cout << "ctor box (material, name, min, max)" << "\n";
    }

Box::~Box() { std::cout << "Box::~Box" << "\n"; }

/* virtual */ double Box::area() const {
    // 6*(area of one side)
    return 6.0 * (std::abs(max_.x - min_.x) * std::abs(max_.x - min_.x));
}

/* virtual */ double Box::volume() const {
  //length * width * height
  return std::abs(max_.x - min_.x) 
    * std::abs(max_.y - min_.y) 
    * std::abs(max_.z - min_.z);
}

/* virtual */ std::ostream& Box::print(std::ostream& os) const {
  os << "\n";
  os << "Box \"" << name() << "\" : \n";
  os << "  name    :  " << name() << "\n";
  os << "  material   :  " << material();

  os << "  minimum :  " 
    << "(" << min().x << "," << min().y << "," << min().z << ")" << "\n";
  
  os << "  maximum :  "
    << "(" << max().x << "," << max().y << "," << max().z << ")" << "\n";
      
  os << "  area    :  " << area() << "\n";
  os << "  volume  :  " << volume() << "\n";

  return os;
}

bool Box::intersect(Ray const& r) const {
  float foo{0.0};
  return Box::intersect(r, foo);
}

bool Box::intersect(Ray const& r, float& dist) const {
  glm::vec3 dir = glm::normalize(r.direction);

  /*
    t-values: scalar of ray vector, 
    calculated by solving ray = min(min_.x, max_x) or ray = max(min_.x, max_.x)
    respectively.
  */

  double tx_min, ty_min, tz_min, tx_max, ty_max, tz_max;

  /*
    tX_min: possible t-values of intersect point on the box side nearer to 
            ray.origin.
    tX_max: possible t-values of  intersect point on the far side of the box.
  */

  if (dir.x != 0) {
    tx_min = (std::min(min_.x - r.origin.x, max_.x - r.origin.x)) / dir.x;
    tx_max = (std::max(min_.x - r.origin.x, max_.x - r.origin.x)) / dir.x;
  } else tx_min = 0;

  if (dir.y != 0) {
    ty_min = (std::min(min_.y - r.origin.y, max_.y - r.origin.y)) / dir.y;
    ty_max = (std::max(min_.y - r.origin.y, max_.y - r.origin.y)) / dir.y;
  } else ty_min = 0;
  
  if (dir.z != 0) {
    tz_min = (std::min(min_.z - r.origin.z, max_.z - r.origin.z)) / dir.z;
    tz_max = (std::max(min_.z - r.origin.z, max_.z - r.origin.z)) / dir.z;
  } else tz_min = 0;

  /*
    tmin: t-value of intersection point on near box side
    tmax: t-value of intersection point on far box side
  */

  double tmin = std::max(std::max(std::min(tx_min, tx_max), 
                  std::min(ty_min, ty_max)), std::min(tz_min, tz_max));

  double tmax = std::min(std::min(std::max(tx_min, tx_max),
                  std::max(ty_min, ty_max)), std::max(tz_min, tz_max));

  //is there a distance between the two intersection points?
  if (tmax < std::max(0.0, tmin)) return false;

  //calculate distance between origin and intersection point:
  dist = std::sqrt( dir.x*(tmin-r.origin.x)*dir.x*(tmin-r.origin.x) 
                        + dir.y*(tmin-r.origin.y)*dir.y*(tmin-r.origin.y)
                        + dir.z*(tmin-r.origin.z)*dir.z*(tmin-r.origin.z) ); 

  //std::cout<<"Do you even intersect? BOX"<< std::endl;
  return true;
}

glm::vec3 Box::intersect_normal(Raystructure const& raystructure) const{
  glm::vec3 center = {((min_.x + max_.x)/2),((min_.y + max_.y)/2),((min_.z + max_.z)/2)};
  glm::vec3 normal = {0.0, 0.0, 0.0};
  float min_distance = std::numeric_limits<float>::max();
  glm::vec3 temp = center; //Statt temp intersection point
  float distance = std::abs(max_.x - std::abs(temp.x));
  if (distance < min_distance) {
		min_distance = distance;
		if ( 0 != temp.x){
		  normal = {(1 * (temp.x/(std::abs(temp.x)))), 0, 0 };
		} else {
			normal = {1, 0, 0 };
		}
  }
  distance = std::abs(max_.y - std::abs(temp.y));
  if (distance < min_distance) {
		min_distance = distance;
    if ( 0 != temp.y){
	    normal = {0, (1 * (temp.y/(std::abs(temp.y)))), 0 };
		} else {
			normal = {0, 1, 0 };
		}
	}
  distance = std::abs(max_.z - std::abs(temp.z));
  if (distance < min_distance) {
		min_distance = distance;
    if ( 0 != temp.z){
      normal = {0, 0, (1 * (temp.z/(std::abs(temp.z))))};		
		} else {
			normal = {0, 0, 1 };
		}
  }
  return normal;
}
