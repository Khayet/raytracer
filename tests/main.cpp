#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sphere.hpp"


TEST_CASE("aufgabe 6.2", "[shapes]") {
  Sphere sph1{}; //default ctor
  glm::vec3 vec{0.0, 0.0, 0.0};
  REQUIRE(sph1.center() == vec);
  Sphere sph2{sph1};  //copy ctor - should be implicitly defined
  REQUIRE(sph2.center() == vec);

  Sphere sph3{glm::vec3{0.0, 0.0, 0.0}, 2.0};
  //REQUIRE(sph3.volume() == Approx(33.5103216383));

}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
