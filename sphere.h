#pragma once
#include "vec3.h"
#include "primitive.h"
class Sphere : public Primitive {
public:

  Sphere(double radius, Vec3 origin): rad(radius), orig(origin) {}
  double radius() const { return rad; }
  Vec3 origin() const { return orig; }

  void setMaterial(Vec3 colour) override {
    this->colour = colour;
  }
 
  HitRecord raycast(Ray ray) override {
    Vec3 oc = ray.origin() - orig;

    double a = dotProduct(ray.direction(), ray.direction());
    double b = 2 * dotProduct(ray.direction(), oc);
    double c = dotProduct(oc, oc) - rad * rad;

    double discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
      return HitRecord{ false };
    }
    // std::clog << "discriminant not 0" << '\n';
    double t = (-b - std::sqrt(discriminant)) / (2.0*a);
    // if (t > 0) {
      // std:: clog << "t value is " << t << '\n';
    // }
    Vec3 point = ray.parametric(t);
    // std::clog << "point of intersection is " << point << '\n';
    Vec3 normal = normalise(point - orig);
    return HitRecord{true, t, point, normal, colour};
  }

private:
  double rad;
  Vec3 orig;
  Vec3 colour = Vec3(0.5,0,0);
};

