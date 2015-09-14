#include "box.hpp"


Box::Box() :
    Shape{},
    min_{glm::vec3{0.0, 0.0, 0.0}},
    max_{glm::vec3{0.0, 0.0, 0.0}} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
    Shape{}, min_{min}, max_{max} {}

Box::Box(Material const& material, std::string const& n,
    glm::vec3 const& min, glm::vec3 const& max) :
    Shape{material, n}, min_{min}, max_{max} {
    }

Box::~Box() {}

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


bool Box::intersect(Ray const& ray, float& dist) const {

  //needed for transformations:
  Ray_T r = ray.transform(world_transformation_inv());
  auto orig = glm::vec3(r.origin);
  auto dir = glm::normalize(glm::vec3(r.direction));

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

  tmin = std::min((min_.x - orig.x) * (1/dir.x), //multiply with inverted vector
                  (max_.x - orig.x) * (1/dir.x));
  tmax = std::max((min_.x - orig.x) * (1/dir.x),
                  (max_.x - orig.x) * (1/dir.x));

  mini = (min_.y - orig.y) * (1/dir.y);
  maxi = (max_.y - orig.y) * (1/dir.y);
  tmin = std::max(tmin, std::min(mini, maxi));
  tmax = std::min(tmax, std::max(mini, maxi));


  mini = (min_.z - orig.z) * (1/dir.z);
  maxi = (max_.z - orig.z) * (1/dir.z);
  tmin = std::max(tmin, std::min(mini, maxi));
  tmax = std::min(tmax, std::max(mini, maxi));

  //is there a distance between the two intersection points?
  if (tmax < std::max<float>(0.0, tmin)) return false;

  //direction is calculated in world coordinate system (not transformed)
  dir = glm::normalize(ray.direction);

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


  float epsilon = 400*min_distance; //arbitrary small number

  glm::vec3 hit = intersection;
  float diff = 0.0;
  diff = hit.x - min_.x;
  if (diff < epsilon) normal = {-1.0, 0.0, 0.0};
  diff = hit.x - max_.x;
  if (diff < epsilon) normal = {1.0, 0.0, 0.0};
  diff = hit.x - min_.y;
  if (diff < epsilon) normal = {0.0, -1.0, 0.0};
  diff = hit.x - max_.y;
  if (diff < epsilon) normal = {0.0, 1.0, 0.0};
  diff = hit.x - min_.z;
  if (diff < epsilon) normal = {0.0, 0.0, 1.0};
  diff = hit.x - max_.z;
  if (diff < epsilon) normal = {0.0, 0.0, -1.0};

  normal = glm::normalize(normal);
  return normal;
}

Raystructure Box::raystruct_intersect(Ray const& r) const {
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
    returner.shape_ptr_ = std::make_shared<Box>(*this);
	}
	return returner;
}

void Box::translate(glm::vec3 const& t_vec) {
  glm::mat4 t_mat{1.0};
  t_mat[3] = glm::vec4(t_vec, 1); //create correct transformation matrix

  set_matrix(t_mat);
}

