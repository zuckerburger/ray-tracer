#pragma once
#include "msaa.h"
#include "vec3.h"
#include <span>

class Camera;
class Canvas;
class Ray;
class Sample;
class Scene;

constexpr Vec3 light_origin(-.75, 1, -1);
constexpr Vec3 light_colour(1, 1, 1);
constexpr Vec3 background(0.4, 0.9, 0.8);

class RayTracingEngine {
public:
  RayTracingEngine() = default;
  void render(Camera &camera, Scene &scene, Canvas &canvas);

  void addMultiSampling(int samplesPerPixel);

  Vec3 calculateColour(Ray &ray, Scene &scene);

private:
  std::span<const Sample> msaaSamples = setMsaa(0);
};
