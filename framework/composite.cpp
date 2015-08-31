#include "../framework/composite.hpp"


Composite::Composite() : Shape{}  {}
Composite::Composite(std::unordered_map<std::string, std::shared_ptr<Shape>> shapes) 
  : Shape{}, children_{shapes} {}
Composite::Composite(Composite const& copy_composite) 
  : Shape{copy_composite.material(), copy_composite.name()}, 
    children_{copy_composite.children_} {}
Composite::Composite(Material const& material, std::string const& n,
    std::unordered_map<std::string, std::shared_ptr<Shape>> shapes) 
    :    Shape{material, n}, children_{shapes} {}
Composite::Composite(
    Material const& material, 
    std::string const& n,
    std::unordered_map<std::string, std::shared_ptr<Shape>> shapes,
    std::unordered_map<std::string, std::shared_ptr<Shape>> database)
    :    Shape{material, n}, children_{shapes}, database_{database} {}
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
  os << "  children    :  ";
  for (auto const& it : children_) {
	  os << " " << it.second->name() << " ";
	}
  os << "\n";
  return os;
}

bool Composite::intersect(Ray const& ray) const{
	float distance = 0.0;
	bool intersect_test = false;
	for (auto it : children_) {
	  intersect_test = it.second->intersect(ray, distance);
	}  
	return intersect_test;
}

bool Composite::intersect(Ray const& ray, float& dist) const{
	bool intersect_test = false;
	for (auto it : children_) {
	  intersect_test = it.second->intersect(ray, dist);
	}  
	return intersect_test;
}

bool Composite::intersect(Ray const& ray, float& dist,std::shared_ptr<Shape> & ptr) const{
	bool intersect_test = false;
	float min_distance = std::numeric_limits<float>::max();	
	for (auto it : children_) {
				std::cout <<"GOT CALLED WHAT IS YOUR INQUIRE?"<< std::endl;
	  intersect_test = it.second->intersect(ray, dist,ptr);
	  std::cout <<"DIST ?:"<<dist << std::endl;
	  		std::cout <<it.second->name()<< std::endl;
	  if (true == intersect_test && min_distance >= dist)
	  {
			min_distance = dist;
			ptr = (it.second);
		}
	}  
	dist = min_distance;
	return intersect_test;
}

/*
Raystructure Composite::intersect(Ray const& ray, float& dist, std::shared_ptr<Shape> & ptr) const{
	

	bool intersect_test = false;
  bool exist_sect = false;
	float min_distance = std::numeric_limits<float>::max();
  float distance = 0;
	std::string correct_child;
	for (auto it : children_) {
	  intersect_test = false;
	  intersect_test = it.second->intersect(ray, dist);
	  if (distance <= min_distance && true == intersect_test) {
		  exist_sect = true;
		  min_distance = distance;
		  correct_child = it.second->name();
		  ptr = (it.second);
		std::cout <<"Name "<< (*it.second)<< std::endl;
		}
	}
	if(exist_sect) {
   
	} 
	 Raystructure intersect_struct(ray.origin, ray.direction, catched_object->mterial().color_ka(),catched_object->material(), distance, ray_depth);
	std::cout << "       " ;
	return intersect_struct;
}*/

bool Composite::intersect_ptr(Ray const& ray, float& dist, std::shared_ptr<Shape> & ptr) const{
	bool intersect_test = false;
  bool exist_sect = false;
	float min_distance = std::numeric_limits<float>::max();
  float distance = 0;
	std::string correct_child;
	for (auto it : children_) {
	  intersect_test = false;
	  intersect_test = it.second->intersect(ray, distance, ptr);
	  if (distance <= min_distance && true == intersect_test) {
		  exist_sect = true;
		  min_distance = distance;
		  correct_child = ptr->name();
		std::cout <<"Name "<< (*it.second)<< std::endl;
		}
	}
	if(exist_sect) {
    auto it = database_.find(correct_child);
   std::cout <<"LOLOOKOAWKOK$$S"<< it->second->name();
  // ptr = (it->second);//ererererotr
    
	} 

	std::cout << "       " ;
	dist = distance;
	return intersect_test;
}


	

glm::vec3 Composite::intersect_normal(Raystructure const& raystructure) const{	
  glm::vec3 normal = {0, 0, 0};
	bool intersect_test = false;
	Ray eyeray = {raystructure.origin_, raystructure.direction_};
	float min_distance = std::numeric_limits<float>::max();
  float distance = 0;
  bool exist_sect = false;
	std::string correct_child;
	for (auto const& it : children_) {
	  intersect_test = false;
	  intersect_test = it.second->intersect(eyeray, distance);
	  if (distance <= min_distance && true == intersect_test) {
		  exist_sect = true;
		  min_distance = distance;
		  correct_child = it.second->name();
		}
	}
	if(exist_sect) {
    auto it = children_.find(correct_child);
	  normal = it->second->intersect_normal(raystructure);
	    std::cout << " Normal (" << normal.x << normal.y << 
	normal.z<< ")  " << std::endl;
	  return normal;
	}
  std::cout << "Error: No children available" << std::endl;
  return {0.0, 0.0, 0.0};
} 

std::unordered_map<std::string ,std::shared_ptr<Shape>> Composite::get_children(){
	return children_;
}

void Composite::add(std::shared_ptr<Shape> const& shape) {
  children_.insert (std::pair<std::string, std::shared_ptr<Shape>>(shape->name(), shape)); 
}

void Composite::remove(std::string const& shape) {
  std::unordered_map<std::string ,std::shared_ptr<Shape>>::iterator it = children_.find(shape);
  children_.erase(it);
}
