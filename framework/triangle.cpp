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

bool Triangle::intersect(Ray const& ray) const {
 float distance = 0.0;
 return intersect(ray, distance);
}

bool Triangle::intersect(Ray const& ray, float& dist) const {
  Ray_T r = ray.transform(world_transformation());
  auto orig = glm::vec3(r.origin);
  auto dir = glm::normalize(glm::vec3(r.direction));
  glm::vec3 straw_man;
  //std::cout<<"Do you even intersect? SPHERE"<< std::endl;
  return glm::intersectRayTriangle(
      orig, dir,
      avertex(), bvertex(),cvertex(), straw_man);
  return true;
}

glm::vec3 Triangle::intersect_normal(Ray const& ray) const{
  glm::vec3 normal = {0.0, 0.0, 0.0};
  return normal;
}

Raystructure Triangle::raystruct_intersect(Ray const& r) const {
  Raystructure returner{r.origin, r.direction, Color{0,0,0}, 
		                  material(), std::numeric_limits<float>::max(),	
		                  glm::vec3{0, 0, 0},false, nullptr};
  bool intersect_test =false;
  float distance = 0;
  intersect_test = intersect(r, distance);
  if (true == intersect_test){
    returner.origin_ = r.origin;
    returner.direction_ = r.direction;
    returner.curr_color_ = Color {0,0,0};
    returner.material_ = material();
    returner.distance_ = distance;
    returner.normal_ = intersect_normal(r); 
    returner.is_hit_= intersect_test;
    returner.shape_ptr_ = std::make_shared<Triangle>(*this);
	}
	return returner;
}


void Triangle::translate(glm::vec3 const& t_vec) {

}

