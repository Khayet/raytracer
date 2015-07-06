#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include "sphere.hpp"
#include "box.hpp"


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
    Color{0.0, 0.0, 0.0}, std::string{},
    glm::vec3{0.0, 0.0, 0.0}, glm::vec3{2.0, -2.0, 2.0}
  };

  REQUIRE(box2.volume() == Approx(8.0));
  REQUIRE(box2.area() == Approx(24.0));
}


TEST_CASE("aufgabe 6.3", "[shapes]") {
  Box box1{};
  REQUIRE(Approx(0.0) == box1.color().r);

  Box box2{glm::vec3{2.0, 33.0, 1.75}, glm::vec3{0.0, 42.0, 2.33}};
  REQUIRE("" == box2.name());

  Box box3{Color{1.0, 0.55, 1.0}, {"box3"}, 
    glm::vec3{2.0, 33.0, 1.75}, glm::vec3{0.0, 42.0, 2.33}};
  REQUIRE("box3" == box3.name());

  Sphere sph1{};
  REQUIRE("" == sph1.name());

  Sphere sph2{glm::vec3{-2.0, 3.0, 11.33}, 0.72};
  REQUIRE(Approx(0.0) == sph2.color().g);

  Sphere sph3{Color{0.88, 1.0, 0.02}, {"sphere3"}, 
    glm::vec3{0.0, 0.52, 1.33}, 12};

  REQUIRE(Approx(0.02) == sph3.color().b);
}

TEST_CASE("aufgabe 6.4", "[print]") {
  Sphere sph1{Color{1.0, 0.55, 0.093}, {"tennis ball"}, glm::vec3{}, 5.12};
  sph1.print(std::cout);

  Box box1{Color{0.0, 1.0, 0.0}, {"green box"}, 
    glm::vec3{}, glm::vec3{2.0, 3.0, 0.33}};
  
  std::cout << box1;
}

TEST_CASE("aufgabe 6.5", "[print_overload]") {
  Box box{Color{1.0, 0.0, 0.0}, {"red box"}, 
    glm::vec3{0.0, 0.0, 0.0}, glm::vec3{2.0, 2.0, 2.0}};

  std::cout << box;

  Sphere sph{Color{0.0, 0.0, 1.0}, {"blue sphere"},
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
  sph.intersect(ray, sph, distance);

  REQUIRE(distance == Approx(5.0f));
}

TEST_CASE("aufgabe 6.8", "[virtual]") {
  Color red(255, 0, 0);
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


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
