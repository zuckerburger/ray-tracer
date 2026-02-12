#pragma once
#include "material.h"
#include "vec3.h"

class Ray;
struct HitRecord {
  bool hit{};
  double t{};
  Vec3 point{};
  Vec3 normal{};
  Material material{};
};

class Primitive {
public:
  Primitive(){};
  virtual HitRecord raycast(const Ray &ray) = 0;
  virtual void setMaterial(const Material &material) = 0;
};
