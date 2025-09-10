#include "hue_shift.h"

#include <iostream>
#include <ostream>

#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  double temp[3];
  double temp2[3];
  for (int i = 0; i < width*height; i ++){
    rgb_to_hsv((double)rgb[i*3]/255,(double)rgb[i*3+1]/255,(double)rgb[i*3+2]/255,temp[0],temp[1],temp[2]);
    //std::cout << temp[0] << ' ' << temp[1] << ' ' << temp[2] << std::endl;
    temp[0] = temp[0] + shift;
    //std::cout << temp[0] << ' ' << temp[1] << ' ' << temp[2] << std::endl;
    hsv_to_rgb(temp[0], temp[1], temp[2], temp2[0], temp2[1], temp2[2]);
    //std::cout << temp2[0] << ' ' << temp2[1] << ' ' << temp2[2] << std::endl;
    shifted[i*3] = (unsigned char)temp2[0] * 255;
    shifted[i*3+1] = (unsigned char)temp2[1] * 255;
    shifted[i*3+2] = (unsigned char)temp2[2] * 255;
  }
}
