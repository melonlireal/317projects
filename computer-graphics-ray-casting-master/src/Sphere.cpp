#include "Sphere.h"

#include "first_hit.h"
#include "Ray.h"
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  if (pow(2*ray.direction.dot(ray.origin - center),2) \
    - 4*((ray.direction.dot(ray.direction))*(ray.origin - center).dot(ray.origin - center)-pow(radius,2)) == 0){
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

