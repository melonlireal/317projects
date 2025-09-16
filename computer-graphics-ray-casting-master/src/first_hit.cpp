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
  double curr_min = -1.0;
  for (int i = 0; i < objects.size(); i++) {
    if (objects[i]->intersect(ray, min_t, t, n)) {
      if (curr_min == -1.0 or curr_min < t) {
        curr_min = t;
        hit_id = i;
      }
    }
  }
  if (curr_min != -1.0) {
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

