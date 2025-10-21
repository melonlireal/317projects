#include "ray_intersect_box.h"
#include <iostream>

#include "igl/max.h"
#include "igl/min.h"

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
    double t_Xmin;
    double t_Xmax;
    double t_Ymin;
    double t_Ymax;
    double t_Zmin;
    double t_Zmax;
    if (ray.direction[0] >= 0) {
      t_Xmin = (box.min_corner[0] - ray.origin[0])/ray.direction[0];
      t_Xmax = (box.max_corner[0] - ray.origin[0])/ray.direction[0];
    }else {
      t_Xmin = (box.max_corner[0] - ray.origin[0])/ray.direction[0];
      t_Xmax = (box.min_corner[0] - ray.origin[0])/ray.direction[0];
    }
    if (ray.direction[1] >= 0) {
      t_Ymin = (box.min_corner[1] - ray.origin[1])/ray.direction[1];
      t_Ymax = (box.max_corner[1] - ray.origin[1])/ray.direction[1];
    }else {
      t_Ymin = (box.max_corner[1] - ray.origin[1])/ray.direction[1];
      t_Ymax = (box.min_corner[1] - ray.origin[1])/ray.direction[1];
    }
    if (ray.direction[2] >= 0) {
      t_Zmin = (box.min_corner[2] - ray.origin[2])/ray.direction[2];
      t_Zmax = (box.max_corner[2] - ray.origin[2])/ray.direction[2];
    }else {
      t_Zmin = (box.max_corner[2] - ray.origin[2])/ray.direction[2];
      t_Zmax = (box.min_corner[2] - ray.origin[2])/ray.direction[2];
    }
    double maxmin = std::max({t_Xmin, t_Ymin, t_Zmin}); // largest min value
    double minmax = std::min({t_Xmax, t_Ymax, t_Zmax}); // smallest max value
    if (maxmin < minmax && maxmin <= max_t && minmax >= min_t){
        return true;
    }
    return false;
  ////////////////////////////////////////////////////////////////////////////
}
