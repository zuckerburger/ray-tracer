#pragma once
#include <vector>
#include <iostream>

#include "msaa.h"
#include "vec3.h"
#include "camera.h"
#include "canvas.h"
#include "ray.h"
#include "scene.h"

constexpr Vec3 light_origin(-0.5,2,0);
constexpr Vec3 light_colour(1,1,1);
constexpr Vec3 background(0,1,0);

class RayTracingEngine {
public:
  RayTracingEngine() = default;
  void render(Camera& camera, Scene& scene, Canvas& canvas) {
    for (int j = 0; j < camera.getImageHeight(); j++) {
      for (int i = 0; i < camera.getImageWidth(); i++) {
        std::vector<Ray> rays;
        rays.reserve(msaaSamples.size());
        for (auto sample: msaaSamples) {
          Ray ray = camera.generateRay(i + sample.sx, j + sample.sy);
          rays.push_back(ray);
        }

        auto object = scene.traceRay(rays[0]).object;
        bool isEdge = false;
        for (auto i = 1; i < rays.size(); i++) {
          auto newObj = scene.traceRay(rays[i]).object;
          if (newObj != object) {
            isEdge = true;
            break;
          }
        }

        Vec3 colour{};
        if (isEdge) {
          Vec3 sum{};
          for (auto ray: rays) {
            sum = calculateColour(ray, scene) + sum;
          }
          colour = sum / rays.size();
        } else {
          colour = calculateColour(rays[0],scene);
        }
        canvas.setPixelByScreen(colour, i, j);
      }
    }
  }

  void addMultiSampling(MsaaOption msaa_option) {
    msaaSamples = setMsaa(msaa_option);
  }

  Vec3 calculateColour(Ray& ray, Scene& scene) {

    RayRecord ray_record = scene.traceRay(ray);
    HitRecord record = ray_record.record;

    if (record.hit) {
      Vec3 light_direction = normalise(light_origin - record.point);
      Ray shadow_ray = Ray(record.point, light_direction);
      HitRecord shadow = scene.traceRay(shadow_ray).record;

      float brightness = 0.1;
      if (shadow.hit == false) {
        brightness = std::max(0.0, dotProduct(record.normal, light_direction));
      }
      Vec3 new_color = record.color * brightness +
        light_colour * brightness * brightness * brightness;

      return new_color;
    }

    return background;
  }

private:
  std::span<const Sample> msaaSamples = setMsaa(NO_MSAA);
};
