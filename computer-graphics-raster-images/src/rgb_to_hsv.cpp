#include "rgb_to_hsv.h"

#include <algorithm>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double M = std::max({r,g,b}); // maximum rgb color
  double m = std::min({r,g,b}); // minimum rgb color
  double C = M - m; // range

  if (r>=g && r>=b) { // r is max
    h = ((g-b)/C + 0) * 60; // cuz you cant use % on double
  }else if (g>=r && g>=b) { // g is max
    h = ((b-r)/C + 2) * 60;
  }else if (b>=r && b>=g) { // b is max
    h = ((r-g)/C + 4) * 60;
  }
  if (M == 0) {
    s = 0;
  } else {
    s = C/M;
  }
  v = M;
  ////////////////////////////////////////////////////////////////////////////
}
