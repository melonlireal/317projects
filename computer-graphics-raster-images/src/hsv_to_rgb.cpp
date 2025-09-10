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
  double H_alt = remainder(h,360)/60;
  double X =c*(1-std::abs((remainder(H_alt,2))-1));

  if (remainder(h,360)<60) {
    r = c + m;
    g = X+m;
    b = m;
  }else if (remainder(h,360) < 120) {
    r = X+m;
    g = c + m;
    b = m;
  }else if (remainder(h,360) < 180) {
    r = m;
    g = c + m;
    b = X+m;
  }else if (remainder(h,360) < 240) {
    r = m;
    g = X+m;
    b = c + m;
  }else if (remainder(h,360) < 300) {
    r = X+m;
    g = m;
    b = c + m;
  }else if (remainder(h,360) < 360) {
    r = c + m;
    g = m;
    b = X + m;
  }
  ////////////////////////////////////////////////////////////////////////////
}
