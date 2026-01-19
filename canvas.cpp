#include "canvas.h"
#include <math.h>

Canvas::Canvas(int width, int height) {
  pixels = *new std::vector<Pixel>(width * height);
  this->width = width;
  this->height = height;
}
void Canvas::writeHeader() {
  output << "P3\n" << width << " " << height << '\n' << maxColour << '\n';
}

void Canvas::writePixel(Pixel pixel) {
  output << int(pixel.red) << ' ' << int(pixel.green) << ' ' << int(pixel.blue)
         << '\n';
}

void Canvas::setPixelByCartesian(Pixel pixel, int x, int y) {
  // Convert cartesian coordinates to pixel index
  x += floor(width / 2);
  y = (-y) + floor(height / 2);

  setPixelByIndex(pixel, y * width + x);
}

void Canvas::setPixelByIndex(Pixel pixel, int index) {
  if (index < 0 || index >= width * height) {
    return;
  }

  pixels[index] = pixel;
}

void Canvas::createImage() {
  writeHeader();
  for (Pixel pixel : pixels) {
    writePixel(pixel);
  }
}
