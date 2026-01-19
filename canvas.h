#pragma once
#include <iostream>
#include <ostream>
#include <vector>
struct Pixel {
  uint8_t red = 255;
  uint8_t green = 255;
  uint8_t blue = 255;
};

class Canvas {

private:
  std::vector<Pixel> pixels;
  std::ostream &output = std::cout;
  int maxColour = 255;
  int width;
  int height;

  void writeHeader();

  void writePixel(Pixel pixel);

public:
  Canvas(int width, int height);

  void setPixelByCartesian(Pixel pixel, int x, int y);
  void setPixelByIndex(Pixel pixel, int index);
  void createImage();
};
