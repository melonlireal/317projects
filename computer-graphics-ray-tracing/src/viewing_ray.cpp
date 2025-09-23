#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  double u = (camera.width/(double)width) * (j + 0.5) - camera.width/2.0; // plus 0.5 cuz origin is on upper left
  double v = (camera.height/(double)height) * (height - i + 0.5) - camera.height/2.0;
  //use plus cuz on top left corner
  ray.origin = camera.e;
  ray.direction = - camera.w * camera.d + camera.u * u + camera.v * v;
  ////////////////////////////////////////////////////////////////////////////
}
