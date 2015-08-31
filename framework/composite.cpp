#include "../framework/composite.hpp"

Composite::Composite() : Shape{}  {}
Composite::Composite(std::vector<std::shared_ptr<Shape>> shapes) :
 Shape{}, children_{shapes} {}
Composite::Composite(Composite const& copy_composite) :
 children_{copy_composite.children_} {}
Composite::~Composite(){}

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
  os << "  name    :  ";
  for (auto it : children_) {
	  os << " " << it-> name() << " ";
	}
  os << "\n";
  return os;
}

bool Composite::intersect(Ray const& ray) const{
	float distance = 0.0;
	bool intersect_test = false;
	for (auto it : children_) {
	  intersect_test = it->intersect(ray, distance);
	}  
	return intersect_test;
}

bool Composite::intersect(Ray const& ray, float& dist) const{
	bool intersect_test = false;
	for (auto it : children_) {
	  intersect_test = it->intersect(ray, dist);
	}  
	return intersect_test;
}

glm::vec3 Composite::intersect_normal(Raystructure const& raystructure) const{	
  glm::vec3 normal = {0, 0, 0};
	bool intersect_test = false;
	Ray eyeray = {raystructure.origin_, raystructure.direction_};
	float min_distance = std::numeric_limits<float>::max();
  float distance = 0;
	int i = 0;
	int shape_index = 0;
	for (auto it : children_) {
	  intersect_test = it->intersect(eyeray, distance);
	  if (distance <= min_distance) {
		  min_distance = distance;
		  shape_index = i;
		}
	  i++;	  
	  normal = children_[shape_index]->intersect_normal(raystructure);
	  return normal;
	  }
  std::cout << "Error: No children available" << std::endl;
  return {0.0, 0.0, 0.0};
} 

std::vector<std::shared_ptr<Shape>> Composite::get_children(){
	return children_;
}

void Composite::add(std::shared_ptr<Shape> const& shared_shape) {
 children_.push_back(shared_shape);  
}

void Composite::remove(std::shared_ptr<Shape> const& shared_shape) {
	int i = 0;
	for (auto it : children_) { 
	  if (shared_shape->name() == (*it).name()) {
		  children_.erase(children_.begin() + i);
		}
    i++;
  }
}
