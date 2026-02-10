#pragma once
#include "vec3.h"

class Ray;

class Camera {
public:
  Camera(Vec3 cam_origin, double image_width = 1600, double image_height = 900,
         double focal_length = 1)
      : origin{cam_origin}, image_width{image_width},
        image_height{image_height}, focal_length{focal_length} {}

  // Update internal state of camera data
  void updateViewport();

  double getImageWidth() const { return image_width; }
  double getImageHeight() const { return image_height; }

  void setResolution(double width, double height);
  void setFocalLength(double focal_length);

  Ray generateRay(double x, double y);

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
