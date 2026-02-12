#include "scene.h"
#include "triangle.h"
#include <sstream>

namespace MeshLoader {

void addTriangles(Scene &scene) {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream line_stream(line);
    std::vector<Vec3> points(3);
    for (auto &p : points) {
      line_stream >> p.x >> p.y >> p.z;
    }
    auto new_triangle =
        std::make_shared<Triangle>(points[0], points[1], points[2]);
    scene.addPrimitive(new_triangle);
  }
}
} // namespace MeshLoader
