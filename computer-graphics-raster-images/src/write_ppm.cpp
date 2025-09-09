#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string &filename,
  const std::vector<unsigned char> &data,
  const int width,
  const int height,
  const int num_channels) {
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  // reference: https://www.youtube.com/watch?v=HGHbcRscFsg&ab_channel=Ferrabacus
  std::ofstream ppm(filename);
  if (ppm.is_open()) {
    if (num_channels == 3) {
      ppm << "P3\n";
    } else if (num_channels == 1) {
      ppm << "P2\n";
    }
    ppm << width << " " << height << "\n";
    ppm << "255\n";
    for (int i = 0; i < width * height * num_channels; i++) {
      ppm << (int)data[i] << " ";
    }
    ppm.close();
    std::cout << "Writing PPM image to " << filename << std::endl;
    return true;
  }
  std::cout << "Could not open file " << filename << std::endl;
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
