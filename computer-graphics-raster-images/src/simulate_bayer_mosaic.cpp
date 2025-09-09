#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      if (j%2 == 0) { // this means in the GBGBGB row
        if (i%2 == 0) { //green
          bayer[i*width+j] = rgb[(i*width+j)*3 + 1];
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
  }
  ////////////////////////////////////////////////////////////////////////////
