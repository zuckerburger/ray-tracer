#pragma once
#include <memory>
#include <vector>
#include "primitive.h"
#include <iostream>

struct RayRecord {
  HitRecord record{};
  std::shared_ptr<Primitive> object;
};

class Scene {
public:
  void addPrimitive(std::shared_ptr<Primitive> object) {
    primitives.push_back(object);
  }

  RayRecord traceRay(Ray ray) {
    HitRecord closest_hit{false, -1};
    std::shared_ptr<Primitive> object;

    for (auto& obj: primitives) {
      HitRecord current_record = obj->raycast(ray);

      if (current_record.hit && current_record.t >= 0) {
        if (!closest_hit.hit || closest_hit.t > current_record.t) {
          closest_hit = current_record;
          object = obj;
        }
      }
    }

    return RayRecord(closest_hit, object);
  }
private:
  std::vector<std::shared_ptr<Primitive>> primitives{};
  // std::vector<PointLight> point_lights;
  // std::vector<DirectionLight> direction_lights;
};

