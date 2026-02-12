#include "material.h"
#include "random.h"
#include "ray.h"
#include "vec3.h"

void Material::setColour(Vec3 colour) { this->colour = colour; }
void Material::setSmoothness(float smoothness) {
  this->smoothness = smoothness;
}

Vec3 Material::calculateReflection(const Ray &incoming_ray,
                                   const Vec3 &surface_normal,
                                   Vec3 &incoming_light, uint32_t seed) {
  double epsilon = 1e-8;
  Vec3 outgoing_ray_direction{};
  // Randomly decide between specular or diffuse reflection from smoothness
  double specular_probability = random_double(0, 1, seed);

  if (specular_probability >= this->smoothness) {
    // Random uniform distribution of outgoing ray
    incoming_light = incoming_light * this->colour;
    outgoing_ray_direction = normalise(random_vector(-1, 1, seed));
    if (dotProduct(outgoing_ray_direction, incoming_ray.direction()) < 0) {
      outgoing_ray_direction = outgoing_ray_direction * -1;
    }
  } else {
    outgoing_ray_direction = normalise(random_vector(-1, 1, seed));
    auto d = incoming_ray.direction();
    auto n = surface_normal;

    // Reflection formula
    outgoing_ray_direction = d - 2 * dotProduct(d, n) * n;
  }

  // Return zero vector if no light reflected
  return outgoing_ray_direction;
}
