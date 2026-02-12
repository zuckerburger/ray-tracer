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
                           Vec3 &incoming_light, Vec3 &light_colour,
                           uint32_t seed);
  void setSmoothness(float smoothness);
  void setColour(Vec3 colour);
  void setEmission(float emission_strength,
                   Vec3 emission_colour = Vec3{.9, .9, .9});

private:
  float smoothness;
  Vec3 colour;
  Vec3 specular_colour{.9, .9, .9};

  float emission_strength;
  Vec3 emission_colour;
};
