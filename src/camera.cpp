#include "camera.h"
#include "ray.h"

void Camera::setResolution(double width, double height) {
  image_width = width;
  image_height = height;
  viewport_dirty = true;
}
void Camera::setFocalLength(double focal_length) {
  this->focal_length = focal_length;
  viewport_dirty = true;
}

void Camera::updateViewport() {
  auto viewport_width = viewport_height * double(image_width) / image_height;

  auto viewport_xv = Vec3(viewport_width, 0, 0);
  auto viewport_yv = Vec3(0, -viewport_height, 0);
  auto viewport_origin = origin + Vec3(0, 0, this->focal_length) -
                         viewport_xv / 2 - viewport_yv / 2;

  this->pixel_width = viewport_xv / image_width;
  this->pixel_height = viewport_yv / image_height;
  this->pixel_origin = viewport_origin + pixel_width / 2 + pixel_height / 2;
  viewport_dirty = false;
}

Ray Camera::generateRay(double x, double y) {
  // only update viewport when needed to avoid wasted calculations
  if (viewport_dirty == true) {
    updateViewport();
  }

  Vec3 pixel_center = pixel_origin + (x * pixel_width) + (y * pixel_height);
  Vec3 ray_direction = pixel_center - origin;

  return Ray(pixel_center, ray_direction);
}
