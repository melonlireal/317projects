#include "triangle_area_normal.h"
#include <Eigen/Geometry>

Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
  ////////////////////////////////////////////////////////////////////////////
  Eigen::RowVector3d t1 = b - a;
  Eigen::RowVector3d t2 = c - a;
  return t1.cross(t2)/2;
}
