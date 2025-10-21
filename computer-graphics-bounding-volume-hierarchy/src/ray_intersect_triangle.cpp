#include "ray_intersect_triangle.h"
#include <Eigen/Dense>

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d V1 = A;
  Eigen::Vector3d V2 = B;
  Eigen::Vector3d V3 = C;
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d T1 = V2 - V1;
  Eigen::Vector3d T2 = V3 - V1;

  Eigen::Matrix3d M;
  M << T1(0), T2(0),-d(0),
      T1(1), T2(1),-d(1),
      T1(2), T2(2),-d(2);

  Eigen::Vector3d temp = M.inverse() * (e-V1);

  if (0 <= temp(0) && 0 <= temp(1) && temp(0) + temp(1) <= 1 \
    && temp(2) >= min_t && temp(2) <= max_t) {
    t = temp(2);
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

