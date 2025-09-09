#include "rgba_to_rgb.h"

#include <iostream>

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  for (int i = 0; i < width*height; i ++){
    for (int j = 0; j < 3; j ++) {
      rgb[i*3 + j] = rgba[i*4 + j];
    }
  }
}
