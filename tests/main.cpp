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

  Box box2{glm::vec3{0.0, 0.0, 0.0}, glm::vec3{2.0, -2.0, 2.0}};
  REQUIRE(box2.volume() == Approx(8.0));
  REQUIRE(box2.area() == Approx(24.0));

}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
