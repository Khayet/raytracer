#include "../framework/composite.hpp"
//

Composite::Composite() : Shape{}  {std::cout << "ctor Composite ()" << name() << "\n"; }
Composite::Composite(std::unordered_map<std::string, std::shared_ptr<Shape>> shapes) 
  : Shape{}, children_{shapes} {std::cout << "ctor Composite ()" << name() << "\n"; }
Composite::Composite(Composite const& copy_composite) 
  : Shape{copy_composite.material(), copy_composite.name()}, 
    children_{copy_composite.children_} {std::cout << "ctor Composite ()" << name() << "\n"; }
Composite::Composite(Material const& material, std::string const& n,
    std::unordered_map<std::string, std::shared_ptr<Shape>> shapes) 
    :    Shape{material, n}, children_{shapes} {std::cout << "ctor Composite ()" << name() << "\n"; }
Composite::Composite(
    Material const& material, 
    std::string const& n,
    std::unordered_map<std::string, std::shared_ptr<Shape>> shapes,
    std::unordered_map<std::string, std::shared_ptr<Shape>> database)
    :    Shape{material, n}, children_{shapes}, database_{database} {std::cout << "ctor Composite ()" << name() << "\n"; }
Composite::~Composite(){}

/* virtual */ double Composite::area() const {
  return 0;
}

/* virtual */ double Composite::volume() const {
  return 0;
}

/* virtual */ std::ostream& Composite::print(std::ostream& os) const {
/*  os << "\n";
  os << "Composite \"" << name() << "\" : \n";
  os << "  name    :  " << name() << "\n";  
  os << "  children    :  ";
  for (auto const& it : children_) {
	  os << " " << it.second->name() << "WHY";
	}
  os << "\n";
  return os;*/
}

bool Composite::intersect(Ray const& ray) const{
	float distance = 0.0;
	return intersect(ray, distance);
}

bool Composite::intersect(Ray const& ray, float& dist) const{
  bool test_sect = false;
	float min_distance = std::numeric_limits<float>::max();
  float distance = 0;
  Raystructure correct_candidate;
	for (auto&& it : children_) {
	  Raystructure struct_candidate = it.second->raystruct_intersect(ray);
	  if (struct_candidate.distance_ < min_distance) {
		  test_sect = true;
		  min_distance = distance;
		  correct_candidate = struct_candidate;
		std::cout <<"Name "<< (*it.second)<< std::endl;
		}
	}
	return test_sect;
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
	for (auto&& it : children_) {
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
}
*/
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

glm::vec3 Composite::intersect_normal(Ray const& ray) const{	
	Raystructure temp_struct = raystruct_intersect(ray);
  glm::vec3 normal = temp_struct.normal_;
  return normal;
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

Raystructure Composite::raystruct_intersect(Ray const& r) const {

  bool exist_sect = false;
	float min_distance = std::numeric_limits<float>::max();
  min_distance = min_distance/2;
  	//std::cout <<"#####MINDISTANCE: " << min_distance<< std::endl;
  float distance = 0;
  Raystructure correct_candidate; 
	for (auto&& it : children_) {
	  Raystructure struct_candidate = it.second->raystruct_intersect(r);
	  if (struct_candidate.distance_ < min_distance && struct_candidate.is_hit_) {
		  exist_sect = true;
		  min_distance = distance;
		  correct_candidate = struct_candidate;
		}
		if(exist_sect == false)
		{
			distance = std::numeric_limits<float>::max();
		}
		//std::cout <<"Name "<< (*it.second) << "Distance "<< struct_candidate.distance_<< std::endl;

	}
	//std::cout << std::endl <<  correct_candidate.material_ << std::endl;
	return correct_candidate;
}
