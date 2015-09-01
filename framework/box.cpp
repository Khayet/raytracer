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
/*  os << "\n";
  os << "Box \"" << name() << "\" : \n";
  os << "  name    :  " << name() << "\n";
  os << "  material   :  " << material();

  os << "  minimum :  " 
    << "(" << min().x << "," << min().y << "," << min().z << ")" << "\n";
  
  os << "  maximum :  "
    << "(" << max().x << "," << max().y << "," << max().z << ")" << "\n";
      
  os << "  area    :  " << area() << "\n";
  os << "  volume  :  " << volume() << "\n";
*/
  return os;
}

bool Box::intersect(Ray const& r) const {
  float foo{0.0};
  return Box::intersect(r, foo);
}

bool Box::intersect(
    Ray const& ray, 
    float& dist, 
    std::shared_ptr<Shape> & ptr) const{
  return Box::intersect(ray, dist);
}


bool Box::intersect(Ray const& r, float& dist) const {
  glm::vec3 dir = glm::normalize(r.direction);

  /*
    t-values: scalar of ray vector, 
    calculated by solving ray = min(min_.x, max_x) or ray = max(min_.x, max_.x)
    respectively.
  */

  /*
    mini: possible t-values of intersect point on the box side nearer to 
            ray.origin.
    maxi: possible t-values of  intersect point on the far side of the box.
    tmin: t-value of intersection point on near box side
    tmax: t-value of intersection point on far box side
  */
  float mini, maxi;
  float tmin, tmax;

  tmin = std::min((min_.x - r.origin.x) * (1/dir.x), //multiply with inverted vector
                  (max_.x - r.origin.x) * (1/dir.x));
  tmax = std::max((min_.x - r.origin.x) * (1/dir.x),
                  (max_.x - r.origin.x) * (1/dir.x));

  mini = (min_.y - r.origin.y) * (1/dir.y);
  maxi = (max_.y - r.origin.y) * (1/dir.y);
  tmin = std::max(tmin, std::min(mini, maxi));
  tmax = std::min(tmax, std::max(mini, maxi));


  mini = (min_.z - r.origin.z) * (1/dir.z);
  maxi = (max_.z - r.origin.z) * (1/dir.z);
  tmin = std::max(tmin, std::min(mini, maxi));
  tmax = std::min(tmax, std::max(mini, maxi));

  //is there a distance between the two intersection points?
  if (tmax < std::max<float>(0.0, tmin)) return false;

  //calculate distance between origin and intersection point (pythagoras):
   dist = std::sqrt(  (dir.x*tmin * dir.x*tmin) 
                    + (dir.y*tmin * dir.y*tmin)
                    + (dir.z*tmin * dir.z*tmin) );
  //std::cout<<"Do you even intersect? BOX"<< std::endl;
  return true;
}

glm::vec3 Box::intersect_normal(Ray const& ray) const{
//	std::cout << " Origin (" << raystructure.origin_.x << raystructure.origin_.y << 
//	raystructure.origin_.z<< ") Direction (" << raystructure.direction_.x << 
//	raystructure.direction_.y<< raystructure.direction_.z << " "<< std::endl;
  float distance_inters = 0;
  bool intersect_test = intersect(ray, distance_inters);
  glm::vec3 intersection = {(distance_inters * ray.direction.x),(distance_inters * ray.direction.y),(distance_inters * ray.direction.z)};
  glm::vec3 center = {((min_.x + max_.x)/2),((min_.y + max_.y)/2),((min_.z + max_.z)/2)};
  glm::vec3 normal = {0.0, 0.0, 0.0};
  float min_distance = std::numeric_limits<float>::max();

  glm::vec3 temp = intersection- center; //Statt temp intersection point
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
  normal = glm::normalize(normal);
  return normal;
}

Raystructure Box::raystruct_intersect(Ray const& r) const {
  bool intersect_test =false;
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
