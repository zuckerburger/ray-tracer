#include "scene.h"
#include "ray.h"

void Scene::addPrimitive(std::shared_ptr<Primitive> object) {
  primitives.push_back(object);
}

RayRecord Scene::traceRay(const Ray &ray) {
  HitRecord closest_hit{false, -1};
  std::shared_ptr<Primitive> object;

  // Check if ray hit any object
  double epsilon = 1e-8;
  for (auto &obj : primitives) {
    HitRecord current_record = obj->raycast(ray);

    if (current_record.hit && current_record.t >= epsilon) {
      if (!closest_hit.hit || closest_hit.t > current_record.t) {
        closest_hit = current_record;
        object = obj;
      }
    }
  }

  return RayRecord(closest_hit, object);
}
