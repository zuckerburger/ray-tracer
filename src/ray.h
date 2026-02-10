#pragma once
#include "vec3.h"

class Ray {
  public:

    Ray(): orig{}, direct{} {}
    Ray(const Vec3& origin, const Vec3& direction): orig{origin}, direct{direction} {}

    Vec3 parametric(double t) const {
      return orig + direct * t;
    }

    Vec3 origin() const { return orig; }
    Vec3 direction() const { return direct; }
  private:
    Vec3 orig{};
    Vec3 direct{};

};
