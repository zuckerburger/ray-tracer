#include "canvas.h"
#include <cstdint>

int main(int argc, char *argv[]) {

  int width = 1920;
  int height = 1080;

  Canvas canvas(width, height);

  for (int i = 0; i < width * height; i++) {
    uint8_t red = (uint8_t)(((float)i / (width * height)) * 255);
    Pixel newPixel = {red, uint8_t(255 - red), 255};
    canvas.setPixelByIndex(newPixel, i);
  }
  canvas.createImage();

  // output.close();
  return 0;
}
