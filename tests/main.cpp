#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

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

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
