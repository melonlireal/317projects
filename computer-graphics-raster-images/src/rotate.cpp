#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);

  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < width; i ++) {
    for (int j = 0; j < height; j ++) {
      for (int k = 0; k < num_channels; k ++) {
        rotated[(((width - i )*(height))-(height-j))*num_channels + k] = input[(j*width + i)*num_channels + k];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
