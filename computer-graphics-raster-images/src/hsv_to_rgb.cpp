#include "hsv_to_rgb.h"

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
  r = 0;
  g = 0;
  b = 0;
  double c = v * s;
  double m = v - c;
  if (h<60) {
    r = c + m;
    g = 0;
    b = m;
  }else if (h < 120) {
    r = 0;
    g = c + m;
    b = m;
  }else if (h < 180) {
    r = m;
    g = c + m;
    b = 0;
  }else if (h < 240) {
    r = m;
    g = 0;
    b = c + m;
  }else if (h < 300) {
    r = 0;
    g = m;
    b = c + m;
  }else if (h < 360) {
    r = c + m;
    g = m;
    b = 0;
  }
  ////////////////////////////////////////////////////////////////////////////
}
