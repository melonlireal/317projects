#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d point = ray.origin + t * ray.direction;
  for (int i = 0; i < lights.size(); i++) {
    Eigen::Vector3d temp_d;
    double temp_max_t;
    Ray temp_ray;
    lights[i]->direction(point, temp_d, temp_max_t);
    temp_ray.origin = point;
    temp_ray.direction = temp_d;
    int temp_hit_id;
    double temp_t;
    Eigen::Vector3d temp_n;
    if (!first_hit(temp_ray,0,objects,temp_hit_id,temp_t,temp_n)) {// if didn'y hit anything

    }
  }
  return Eigen::Vector3d(0,0,0);
  ////////////////////////////////////////////////////////////////////////////
}
