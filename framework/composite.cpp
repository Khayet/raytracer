#include "composite.hpp"

Composite::Composite() : Shape{} {}
Composite::Composite(std::vector<Shape> shapes) :
 : Shape{}, shapes_{shapes} {}
~Composite();

glm::vec3 Composite::shapes() const { return shapes_; }
 
/* virtual */ double Composite::area() const {
  return 0;
}

/* virtual */ double Composite::volume() const {
  return 0;
}

/* virtual */ std::ostream& Composite::print(std::ostream& os) const {
  os << "\n";
  os << "Composite \"" << name() << "\" : \n";
  os << "  name    :  " << name() << "\n";
  os << "  name    :  " << get_children() << "\n";

  return os;
}

bool Composite::intersect(Ray const&) const{return true;}
bool Composite::intersect(Ray const&, float& dist) {return true;};
glm::vec3 Composite::intersect_normal(glm::vec3 const& intersection) const
{0,0,0};
auto Composite::get_children(){
	return shapes_;
}

void Composite::add(std::shared_ptr<Shape> shape_ptr) {
  auto shared_shape = std::make_shared<Shape>(shape);
  shapes_.push_back(shared_shape);  
}

void Composite::remove(Shape const& shape) {
	int i = 0;
	for (auto it : shapes_) { 
  auto shared_shape = std::make_shared<Shape>(shape);
	  if (true == (*it).name_) {
		  vec.erase(vec.begin() + i);		  
		}
    i++;
  }
}
