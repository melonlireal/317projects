#include "hsv_to_rgb.h"

#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double c = v * s;
  double m = v - c;
  double H_alt = fmod(h,360.0)/60.0;
  double X =c*(1-std::abs((fmod(H_alt,2.0))-1.0));

  if (H_alt < 1) {
    r = c + m;
    g = X + m;
    b = m;
  }else if (H_alt < 2) {
    r = X + m;
    g = c + m;
    b = m;
  }else if (H_alt < 3) {
    r = m;
    g = c + m;
    b = X + m;
  }else if (H_alt < 4) {
    r = m;
    g = X + m;
    b = c + m;
  }else if (H_alt < 5) {
    r = X + m;
    g = m;
    b = c + m;
  }else if (H_alt < 6) {
    r = c + m;
    g = m;
    b = X + m;
  }
  ////////////////////////////////////////////////////////////////////////////
}
