#include "ray_tracing_engine.h"
#include "camera.h"
#include "canvas.h"
#include "msaa.h"
#include "ray.h"
#include "scene.h"

void RayTracingEngine::render(Camera &camera, Scene &scene, Canvas &canvas) {
  // Loop over every pixel in the image
  for (int j = 0; j < camera.getImageHeight(); j++) {
    for (int i = 0; i < camera.getImageWidth(); i++) {
      std::vector<Ray> rays;
      rays.reserve(msaaSamples.size());

      // Generate a ray for each sample
      for (auto sample : msaaSamples) {
        Ray ray = camera.generateRay(i + sample.sx, j + sample.sy);
        rays.push_back(ray);
      }

      // Pixel is an edge if samples hit different objects
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

      // For edge pixels, take the average of each samples colour
      if (isEdge) {
        Vec3 sum{};
        for (auto ray : rays) {
          sum = calculateColour(ray, scene) + sum;
        }
        colour = sum / rays.size();
      } else {
        colour = calculateColour(rays[0], scene);
      }
      canvas.setPixelByScreen(colour, i, j);
    }
  }
}

void RayTracingEngine::addMultiSampling(int samplesPerPixel) {
  msaaSamples = setMsaa(samplesPerPixel);
}

Vec3 RayTracingEngine::calculateColour(Ray &ray, Scene &scene) {

  RayRecord ray_record = scene.traceRay(ray);
  HitRecord record = ray_record.record;

  if (record.hit) {
    Vec3 light_direction = normalise(light_origin - record.point);
    Ray shadow_ray = Ray(record.point, light_direction);
    HitRecord shadow = scene.traceRay(shadow_ray).record;
    double epsilon = 1.e-6;
    double brightness = 0.1;

    // Epsilon accounts for floating point error
    if (shadow.hit == false or shadow.t < epsilon) {
      // Use angle between light and surface normal to calculate brightness
      brightness = std::max(0.0, dotProduct(record.normal, light_direction));
    }

    // Brightness cubed for gamma correction
    Vec3 new_color = record.colour * brightness +
                     light_colour * brightness * brightness * brightness;

    return new_color;
  }

  return background;
}
