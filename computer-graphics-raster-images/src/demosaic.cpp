#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      if (j%2 == 0) { // this means in the GBGBGB row
        if (i%2 == 0) { //green pixel
          rgb[i*3+0] = bayer[i*3+0];
        }else if (i%2 == 1) { //blue
          bayer[i*width+j] = rgb[(i*width+j)*3+3];
        }
      }else if (j%2 == 1) {
        // RGRGRGRG row
        if (i%2 == 0) { // red
          bayer[i*width+j] = rgb[(i*width+j)*3];
        }else if (i%2 == 0) { // green
          bayer[i*width+j] = rgb[(i*width+j)*3 + 1];
        }
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

bool help_exists(int num, int width, int height) {
  if (0 < num < width * height) {
    return true;
  }
  return false;
}
