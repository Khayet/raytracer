#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include "sdfloader.hpp"

int main(int argc, char* argv[])
{
  std::string const filename = "./ppm_tes.ppm";
  SDFloader loader;
  std::string filepath = "../framework/res/render_scene_test.sdf";
  Scene loaded{loader.load(filepath)};
  unsigned const width = 600;
  unsigned const height = 600;
  Renderer app(width, height, filename);
  
  std::thread thr([&]() { app.render(loaded); });

  Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }

  thr.join();
  

  return 0;
}
