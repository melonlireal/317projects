#include "rgb_to_hsv.h"

#include <algorithm>
#include <cmath>

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

  if (C==0) {
    h = 0;
  }else if (r==M) { // r is max
    h = (fmod((g-b)/C, 6.0)) * 60;
  }else if (g==M) { // g is max
    h = (((b-r)/C) + 2) * 60;
  }else if (b==M) { // b is max
    h = (((r-g)/C) + 4) * 60;
  }
  if (M == 0) {
    s = 0;
  } else {
    s = C/M;
  }
  v = M;
  ////////////////////////////////////////////////////////////////////////////
}
