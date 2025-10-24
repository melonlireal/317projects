#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////
  const double PI = atan(1) * 4;
  Eigen::MatrixXd face_normals(F.rows(), 3);
  Eigen::MatrixXd face_area_normals(F.rows(), 3);

  for (int i = 0; i < F.rows(); i++) {
    const Eigen::RowVector3d& a = V.row(F(i, 0));
    const Eigen::RowVector3d& b = V.row(F(i, 1));
    const Eigen::RowVector3d& c = V.row(F(i, 2));

    face_area_normals.row(i) = triangle_area_normal(a, b, c);
    face_normals.row(i) = face_area_normals.row(i).normalized();
  }

  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F, V.rows(), VF);


  for (int j = 0; j < F.rows(); j++) {
    for (int k = 0; k < 3; k++) {
      Eigen::RowVector3d weighted_sum = Eigen::RowVector3d::Zero();
      // Get the normal of the current face
      Eigen::RowVector3d current_face_normal = face_normals.row(j);

      // Sum area-weighted normals from incident faces within threshold
      for (int j = 0; j < VF[F(j, k)].size(); j++) {
        int neighbor_face_idx = VF[F(j, k)][j];
        Eigen::RowVector3d neighbor_face_normal = face_normals.row(neighbor_face_idx);

        // Check if within threshold
        double dot_product = current_face_normal.dot(neighbor_face_normal);
        if (dot_product >= std::cos(corner_threshold * PI / 180.0)) {
          weighted_sum += face_area_normals.row(neighbor_face_idx);
        }
      }

      // Normalize the result to get unit normal
      if (weighted_sum.norm() > 0) {
        N.row(j * 3 + k) = weighted_sum.normalized();
      } else {
        // Fallback: use the current face's normal if no neighbors pass threshold
        N.row(j * 3 + k) = current_face_normal;
      }
    }
  }
}
