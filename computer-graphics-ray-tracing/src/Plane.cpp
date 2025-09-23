#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  if (ray.direction.dot(normal) != 0) {
    double temp_t = -normal.dot(ray.origin-point) / normal.dot(ray.direction);
    //std::cout << temp_t << std::endl;
    if (temp_t >= min_t) {
      t = temp_t;
      n = normal;
      return true;
    }
  }
  // reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

