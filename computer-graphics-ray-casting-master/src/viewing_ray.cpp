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
  double u = (camera.width/width) * (j + 0.5) - camera.width/2;
  double v = (camera.height/height) * (i + 0.5) + camera.height/2;
  //use plus cuz on top left corner
  ray.origin = camera.e;
  ray.direction = - camera.w * camera.d + camera.u * u + camera.v * v;
  // from text book
  ////////////////////////////////////////////////////////////////////////////
}

