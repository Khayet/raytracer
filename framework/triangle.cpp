#include "triangle.hpp"


Triangle::Triangle() : 
    Shape{},
    avertex_{glm::vec3{0.0, 0.0, 0.0}},
    bvertex_{glm::vec3{0.0, 0.0, 0.0}} { /*std::cout << "ctor box ()" << "\n";*/ }

Triangle::Triangle(
  glm::vec3 const& avertex, 
  glm::vec3 const& bvertex, 
  glm::vec3 const& cvertex) : 
    Shape{}, avertex_{avertex}, bvertex_{bvertex}, cvertex_{cvertex} { /*std::cout << "ctor box (min, max)" << "\n";*/}

Triangle::Triangle(Material const& material, std::string const& n,
    glm::vec3 const& avertex, 
    glm::vec3 const& bvertex, 
    glm::vec3 const& cvertex) :
    Shape{material, n}, avertex_{avertex}, bvertex_{bvertex}, cvertex_{cvertex} {
      //std::cout << "ctor box (material, name, min, max)" << "\n";
    }

Triangle::~Triangle() { std::cout << "Triangle::~Triangle" << "\n"; }

/* virtual */ double Triangle::area() const {
return 0;
}

/* virtual */ double Triangle::volume() const {
 return 0;
}

/* virtual */ std::ostream& Triangle::print(std::ostream& os) const {
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

bool Triangle::intersect(Ray const& r) const {
 return true;
}

bool Triangle::intersect(Ray const& r, float& dist) const {
  return true;
}

glm::vec3 Triangle::intersect_normal(Ray const& ray) const{
  glm::vec3 normal = {0.0, 0.0, 0.0};
  return normal;
}

Raystructure Triangle::raystruct_intersect(Ray const& r) const {
  bool intersect_test =false;
  float distance = 0;
  intersect_test = intersect(r, distance);
  if (true == intersect_test){
    return Raystructure{r.origin, r.direction, Color{0,0,0}, 
		                  material(), distance,	intersect_normal(r),intersect_test};
	}
	return Raystructure{r.origin, r.direction, Color{0,0,0}, 
		                  material(), std::numeric_limits<float>::max(),	
		                  glm::vec3{0, 0, 0},intersect_test};
}

void Triangle::translate(glm::vec3 const& t_vec) {

}

