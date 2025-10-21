#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  Eigen::Vector3d temp = p - q;
  d = temp.normalized();
  max_t = temp.norm();
  ////////////////////////////////////////////////////////////////////////////
}
