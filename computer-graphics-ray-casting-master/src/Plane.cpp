#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
if (ray.direction.dot(normal) != 0) {
  double temp_t = normal.dot(point - ray.origin) / normal.dot(ray.direction);
  if (temp_t > min_t) {
    t = temp_t;
    n = normal;
    return true;
  }
}
  // reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

