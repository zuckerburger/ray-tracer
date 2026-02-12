#pragma once
#include "vec3.h"
#include <cstdint>

class Ray;

class Material {
public:
  Material() : colour{}, smoothness{} {};
  Material(Vec3 colour, float smoothness = 0.0f)
      : colour{colour}, smoothness{smoothness} {}

  Vec3 calculateReflection(const Ray &incoming_ray, const Vec3 &surface_normal,
                           Vec3 &light_intensity, uint32_t seed);
  void setSmoothness(float smoothness);
  void setColour(Vec3 colour);

private:
  Vec3 colour;
  float smoothness;
};
