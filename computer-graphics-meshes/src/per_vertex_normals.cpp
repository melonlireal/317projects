#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"
void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);

  std::vector<std::vector<int>> VF; // find all adjacent face
  vertex_triangle_adjacency(F, V.rows(), VF);

  for (int i = 0; i < V.rows(); i++) {
    Eigen::RowVector3d weighted_sum = Eigen::RowVector3d::Zero();

    // Sum area-weighted normals
    for (int j = 0; j < VF[i].size(); j++) {

      const Eigen::RowVector3d& a = V.row(F(VF[i][j], 0));
      const Eigen::RowVector3d& b = V.row(F(VF[i][j], 1));
      const Eigen::RowVector3d& c = V.row(F(VF[i][j], 2));
      weighted_sum += triangle_area_normal(a, b, c);
    }

    if (weighted_sum.norm() > 0) {
      N.row(i) = weighted_sum.normalized();
    } else {
      // If sum is zero, set to zero vector
      N.row(i) = Eigen::RowVector3d::Zero();
    }
  }
}
