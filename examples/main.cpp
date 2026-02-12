#include "camera.h"
#include "canvas.h"
#include "material.h"
#include "msaa.h"
#include "ray_tracing_engine.h"
#include "scene.h"
#include "sphere.h"
#include "vec3.h"
#include <memory>

int main(int argc, char **argv) {

  Scene scene;
  Vec3 sphere_origin = Vec3(0, 0, 2);
  float radius = 0.5;
  Vec3 red = Vec3(0.9, 0.2, 0.2);
  float smoothness = 0;

  auto sphere = std::make_shared<Sphere>(radius, sphere_origin);
  Material sphereMaterial = Material{red, smoothness};
  sphere->setMaterial(sphereMaterial);

  scene.addPrimitive(sphere);

  auto sphere2 = std::make_shared<Sphere>(radius, Vec3(1, 0, 1));
  sphereMaterial.colour = Vec3(0.1, 0.1, 0.9);
  sphere2->setMaterial(sphereMaterial);

  auto sphere3 = std::make_shared<Sphere>(radius, Vec3(-1, 0, 1));
  sphereMaterial.emission_strength = 4;
  sphereMaterial.colour = Vec3(0.1, 0.9, 0.1);
  sphere3->setMaterial(sphereMaterial);

  scene.addPrimitive(sphere2);
  scene.addPrimitive(sphere3);

  auto ground = std::make_shared<Sphere>(100, Vec3(0, -100.5, 2));
  const Vec3 blue(0.1, 0.2, 0.9);
  ground->setMaterial(blue);
  scene.addPrimitive(ground);
  Vec3 camera_origin(0, 0, -2);
  Camera camera{camera_origin};

  int focal_length = 1;
  int image_height = 720;
  int image_width = image_height * 16.0 / 9;

  camera.setResolution(image_width, image_height);
  camera.setFocalLength(focal_length);

  RayTracingEngine raytracer = RayTracingEngine();

  raytracer.addMultiSampling(MSAA_4X);

  Canvas canvas{image_width, image_height};
  raytracer.render(camera, scene, canvas);
  canvas.createImage();
  return 0;
}
