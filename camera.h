#pragma once
#include "vec3.h"
#include "ray.h"

class Camera {
public:
  Camera(Vec3 cam_origin, double image_width=1600, double image_height=900, double focal_length=1)
    : origin{cam_origin}
    , image_width{image_width}
    , image_height{image_height}
    , focal_length{focal_length} {}

  void updateViewport() {
    auto viewport_width = viewport_height * double(image_width) / image_height;

    auto viewport_xv = Vec3(viewport_width, 0, 0);
    auto viewport_yv = Vec3(0, -viewport_height, 0);
    auto viewport_origin = origin + Vec3(0,0, this->focal_length) - viewport_xv/2 - viewport_yv/2;

    this->pixel_width = viewport_xv / image_width;
    this->pixel_height = viewport_yv / image_height;
    this->pixel_origin = viewport_origin + pixel_width/2 + pixel_height/2;
    viewport_dirty = false;
  }

  double getImageWidth() const { return image_width; }
  double getImageHeight() const { return image_height; }

  void setResolution(double width, double height) {
    image_width = width;
    image_height = height;
    viewport_dirty = true;
  }

  void setFocalLength(double focal_length) {
    this->focal_length = focal_length;
    viewport_dirty = true;
  }

  Ray generateRay(double x, double y) {
    if (viewport_dirty == true) {
      updateViewport();
    }

    Vec3 pixel_center = pixel_origin + (x * pixel_width) + (y * pixel_height);
    Vec3 ray_direction = pixel_center - origin;

    return Ray(origin, ray_direction);
  }

private:
  Vec3 origin;
  double image_width;
  double image_height;
  double focal_length;

  bool viewport_dirty = true;
  const double viewport_height = 1.0;
  Vec3 pixel_origin;
  Vec3 pixel_width;
  Vec3 pixel_height;

};
