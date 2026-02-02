#pragma once
#include "vec3.h"
#include "ray.h"


struct HitRecord {
  bool hit{};
  double t{};
  Vec3 point{};
  Vec3 normal{};
  Vec3 color{};
};
class Primitive {
public:
  Primitive() {};
  virtual HitRecord raycast(Ray ray) = 0;
  virtual void setMaterial(Vec3 colour) = 0;
};


