#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();
#include <iostream>

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  int hit_index = -1;
  double smallest_sqrD = std::numeric_limits<double>::infinity();
  for (int i = 0; i < points.rows(); ++i) {
    double X = points(i,0);
    double Y = points(i,1);
    double Z = points(i,2);
    double Xd = X - query(0);
    double Yd = Y - query(1);
    double Zd = Z - query(2);
    if (pow(Xd,2) + pow(Yd, 2) + pow(Zd, 2) < smallest_sqrD) {
      hit_index = i;
      smallest_sqrD = pow(Xd,2) + pow(Yd,2) + pow(Zd,2);
    }
  }
  if (hit_index > -1) {
    I = hit_index;
    sqrD = smallest_sqrD;
  }
  ////////////////////////////////////////////////////////////////////////////
}
