#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double curr_min = INFINITY;
  double temp_t;
  Eigen::Vector3d temp_n;
  Eigen::Vector3d curr_eigen;
  for (int i = 0; i < objects.size(); i++) {
    if (objects[i]->intersect(ray, min_t, temp_t, temp_n)) {
      if (curr_min > temp_t) {
        curr_min = temp_t;
        curr_eigen = temp_n;
        hit_id = i;
      }
    }
  }
  if (curr_min != INFINITY) {
    t = curr_min;
    n = curr_eigen;
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

