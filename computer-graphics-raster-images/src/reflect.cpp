#include "reflect.h"

#include <cstring>

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  for(int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      for (int k = 0; k < num_channels; k++) {
        reflected[((width - 1 - i) + j * width) * num_channels + k] = input[(i + j * width) * num_channels + k];
      }
    }
  }
}
