#include "simulate_bayer_mosaic.h"

#include <iostream>

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if ((i%2 == 0 && j%2 == 0) || (i%2 == 1 && j%2 == 1)) { // this means green
          bayer[i * width + j] = rgb[(i * width + j) * 3 + 1];
      }else if (i%2 == 0 && j%2 == 1) { //blue
          bayer[i*width+j] = rgb[(i * width + j) * 3 + 2];
          //std::cout << "this is blue\n";
      }else if (i%2 == 1 && j%2 == 0) { // red
          bayer[i * width + j] = rgb[(i * width + j) * 3];
          //std::cout << "this is red\n";
      }
    }
  }
}

  ////////////////////////////////////////////////////////////////////////////
