#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      gray[i*width + j] = 0.2129 * rgb[(i*width + j)*3 + 0] + 0.7152*rgb[(i*width + j)*3 + 1] + 0.0722*rgb[(i*width + j)*3 + 2];
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}


