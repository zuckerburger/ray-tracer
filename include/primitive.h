#pragma once
#include "vec3.h"

class Ray;
struct HitRecord {
  bool hit{};
  double t{};
  Vec3 point{};
  Vec3 normal{};
  Vec3 colour{};
};
class Primitive {
public:
  Primitive(){};
  virtual HitRecord raycast(const Ray &ray) = 0;
  virtual void setMaterial(const Vec3 &colour) = 0;
};
