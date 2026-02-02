#include "scene.h"
#include "camera.h"
#include "sphere.h"
#include "renderer.h"
#include "ray_tracing_engine.h"
#include "canvas.h"
#include <memory>

int main () {
  Scene scene{};

  Vec3 sphere_origin = Vec3(0,0,2);
  float radius = 0.5;
  auto sphere = std::make_shared<Sphere>(radius, sphere_origin);
  scene.addPrimitive(sphere);

  auto sphere2 = std::make_shared<Sphere>(radius, Vec3(1,0, 3));
  auto sphere3 = std::make_shared<Sphere>(radius, Vec3(-1,0, 3));
  scene.addPrimitive(sphere2);
  scene.addPrimitive(sphere3);

  auto ground = std::make_shared<Sphere>(100, Vec3(0, -100.5, 2));
  const Vec3 blue(0,0.5,0.5);
  ground->setMaterial(blue);
  scene.addPrimitive(ground);
  Vec3 camera_origin{};
  Camera camera{camera_origin};

  int focal_length = 1;
  int image_height = 720;
  int image_width = image_height * 16.0/9;

  camera.setResolution(image_width, image_height);
  camera.setFocalLength(focal_length);

  RayTracingEngine raytracer = RayTracingEngine();

  raytracer.addMultiSampling(MSAA_4X);

  Canvas canvas{image_width, image_height};
  raytracer.render(camera, scene, canvas);
  canvas.createImage();
  return 0;
}
