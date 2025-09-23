#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <iostream>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d V1 = std::get<0>(corners);
  Eigen::Vector3d V2 = std::get<1>(corners);
  Eigen::Vector3d V3 = std::get<2>(corners);
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d T1 = V2 - V1;
  Eigen::Vector3d T2 = V3 - V1;

  Eigen::Matrix3d M;
  M << T1(0), T2(0),-d(0),
      T1(1), T2(1),-d(1),
      T1(2), T2(2),-d(2);

  Eigen::Vector3d temp = M.inverse() * (e-V1);
  if (0 <= temp(0) && 0 <= temp(1) && temp(0) + temp(1) <= 1 && temp(2) >= min_t) {
    t = temp(2);
    n = T1.cross(T2)/((T1.cross(T2)).norm());
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}


