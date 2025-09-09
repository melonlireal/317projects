#include "demosaic.h"

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {

      if (i%2 == 0) { // this means in the GBGBGB row
        if (j%2 == 0) { //green

        }else if (j%2 == 1) { //blue

        }
      }else if (i%2 == 1) {
        // RGRGRGRG row
        if (j%2 == 0) { // red

        }else if (j%2 == 1) { // green

        }
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

