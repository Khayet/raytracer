#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "../framework/sphere.hpp"
#include "../framework/box.hpp"
#include "scene.hpp"
#include "sdfloader.hpp"
#include "composite.hpp"

TEST_CASE("aufgabe 6.2", "[shapes]") {
  Sphere sph1{};
  glm::vec3 vec{0.0, 0.0, 0.0};
  REQUIRE(vec == sph1.center());
  Sphere sph2{sph1};  //implicit copy ctor
  REQUIRE(vec == sph2.center());

  Sphere sph3{glm::vec3{0.0, 0.0, 0.0}, 2.0};
  REQUIRE(sph3.volume() == Approx(33.510321638));
  REQUIRE(sph3.area() == Approx(50.2654824574));

  Box box1{};
  REQUIRE(vec == box1.min());
  REQUIRE(vec == box1.max());

  Box box2{
    Material{}, std::string{},
    glm::vec3{0.0, 0.0, 0.0}, glm::vec3{2.0, -2.0, 2.0}
  };

  REQUIRE(box2.volume() == Approx(8.0));
  REQUIRE(box2.area() == Approx(24.0));
}

TEST_CASE("aufgabe 6.3", "[shapes]") {
  Box box1{};


  Box box2{glm::vec3{2.0, 33.0, 1.75}, glm::vec3{0.0, 42.0, 2.33}};
  REQUIRE("" == box2.name());

  Box box3{Material{}, {"box3"}, 
    glm::vec3{2.0, 33.0, 1.75}, glm::vec3{0.0, 42.0, 2.33}};
  REQUIRE("box3" == box3.name());

  Sphere sph1{};
  REQUIRE("" == sph1.name());

  Sphere sph2{glm::vec3{-2.0, 3.0, 11.33}, 0.72};


  Sphere sph3{Material{}, {"sphere3"}, 
    glm::vec3{0.0, 0.52, 1.33}, 12};
}

TEST_CASE("aufgabe 6.4", "[print]") {
  Sphere sph1{Material{}, {"tennis ball"}, glm::vec3{}, 5.12};
  sph1.print(std::cout);

  Box box1{Material{}, {"green box"}, 
    glm::vec3{}, glm::vec3{2.0, 3.0, 0.33}};
  
  std::cout << box1;
}

TEST_CASE("aufgabe 6.5", "[print_overload]") {
  Box box{Material{}, {"red box"}, 
    glm::vec3{0.0, 0.0, 0.0}, glm::vec3{2.0, 2.0, 2.0}};

  std::cout << box;

  Sphere sph{Material{}, {"blue sphere"},
   glm::vec3{0.0, 0.0, 0.0}, 3.242};

  std::cout << sph;
}

TEST_CASE("intersectRaySphere", "[intersect]") {
  // Ray
  glm::vec3 ray_origin(0.0,0.0,0.0);
  // ray direction has to be normalized !
  // you can use:
  //  v = glm::normalize(some_vector)
  glm::vec3 ray_direction(0.0,0.0,1.0);

  // Sphere
  glm::vec3 sphere_center(0.0,0.0,5.0);
  float sphere_radius(1.0);

  float distance(0.0);
  auto result = glm::intersectRaySphere(
      ray_origin, ray_direction,
      sphere_center, sphere_radius,
      distance);
  REQUIRE(distance == Approx(4.0f));
}

TEST_CASE("aufgabe 6.6" , "[intersect]") {
  Ray ray{{0.0,0.0,0.0}, glm::vec3{0.0, 0.0, 2.0}};
  Sphere sph{{0.0,0.0,0.0}, 5.0};

  float distance = 0.0;
  sph.intersect(ray, distance);

  REQUIRE(distance == Approx(5.0f));
}

TEST_CASE("aufgabe 6.8", "[virtual]") {
	Color red_color(255,0,0);
  Material red{red_color, red_color,red_color};
  //glm::vec3 position(0,0);
  glm::vec3 position{0.0,0.0,0.0};
	
  Sphere* s1 = new Sphere(position, 1.2, red, "sphere0");
  Shape* s2 = new Sphere(position, 1.2, red, "sphere1");

  s1->print(std::cout);
  s2->print(std::cout);

  delete s1;
  delete s2;
}

TEST_CASE("aufgabe 6.10", "[intersect]") {
  Ray ray1{{0.0,0.0,0.0}, {1.0,1.0,1.0}};
  Box box1{{2.0,2.0,2.0}, {5.0,5.0,5.0}};

  float distance{0.0};
  box1.intersect(ray1, distance);
  REQUIRE(3.4641016151377544 == Approx(distance));

  REQUIRE(box1.intersect(ray1));
} 

TEST_CASE("aufgabe 8intersect", "[8intersect]") {
  Ray ray1{{0.0,0.0,0.0}, {0, -0.447214, -0.894427}};
  Box box1{{-100, -80, -100}, {100, 80, -200}};

  float distance{0.0};
  bool test = false;
  std::cout << "intersection test";
  test = box1.intersect(ray1, distance);
  REQUIRE(test == true);

  REQUIRE(box1.intersect(ray1));
} 

/* Obsolete intersection need now raystructure
TEST_CASE("Sphere", "[intersect_normal]") {
  Sphere sph{{0.0,0.0,0.0}, 1.0};
  glm::vec3 intersection{1.0, 0.0, 0.0};
  glm::vec3 normal = sph.intersect_normal(intersection);
  REQUIRE(normal.x == 1.0);
  REQUIRE(normal.y == 0.0);
  REQUIRE(normal.z == 0.0);
}
*/

TEST_CASE("SDFloader", "[load]") {
  SDFloader test;
  std::string filepath = "../framework/res/render_scene_test.sdf";
  Scene loaded(test.load(filepath));
}

TEST_CASE("Renderer", "[render]") {
  Composite charl; // Kompositiontest

  SDFloader loader;
  std::string filepath = "../framework/res/test_scene_2.sdf";
  Scene loaded(loader.load(filepath));
  charl.print(std::cout);
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
