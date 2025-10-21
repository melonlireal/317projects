#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  double sqrd = 0.0;
  for (int i = 0; i < 3; i++) {
    if (query[i] < box.min_corner[i]) {
      double d = box.min_corner[i] - query[i];
      sqrd += d * d;
    } else if (query[i] > box.max_corner[i]) {
      double d = query[i] - box.max_corner[i];
      sqrd += d * d;
    }
  }
  return sqrd;
  ////////////////////////////////////////////////////////////////////////////
}
