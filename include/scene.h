#pragma once
#include "primitive.h"
#include <memory>
#include <vector>

class Primitive;

struct RayRecord {
  HitRecord record{};
  std::shared_ptr<Primitive> object;
};

class Scene {
public:
  void addPrimitive(std::shared_ptr<Primitive> object);

  RayRecord traceRay(const Ray &ray);

private:
  std::vector<std::shared_ptr<Primitive>> primitives{};
};
