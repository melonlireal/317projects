#include "sphere.h"
#include <iostream>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  const int num_vertices_u = num_faces_u + 1;
  const int num_vertices_v = num_faces_v + 1;
  const int total_vertices = num_vertices_u * num_vertices_v;
  const int total_faces = num_faces_u * num_faces_v;
  const double PI = atan(1) * 4;

  // Resize output matrices
  V.resize(total_vertices, 3);
  UV.resize(total_vertices, 2);
  NV.resize(total_vertices, 3);
  F.resize(total_faces, 4);
  UF.resize(total_faces, 4);
  NF.resize(total_faces, 4);

  // vertices, UV coordinates, and normals
  for (int i = 0; i < num_vertices_u; i++) {
    for (int j = 0; j < num_vertices_v; j++) {
      const int vertex_index = i * num_vertices_v + j;

      // UV coordinates (parameter space)
      const double u = (double)i / num_faces_u;
      const double v = (double)j / num_faces_v;
      UV(vertex_index, 0) = u;
      UV(vertex_index, 1) = v;

      // Convert to spherical coordinates
      const double theta = 2.0 * PI * u;  // Longitude [0, 2π]
      const double phi = PI * v;          // Latitude [0, π]

      // Convert to Cartesian coordinates (unit sphere)
      V(vertex_index, 0) = sin(phi) * cos(theta);
      V(vertex_index, 1) = sin(phi) * sin(theta);
      V(vertex_index, 2) = cos(phi);

      // For unit sphere, normals = positions
      NV.row(vertex_index) = V.row(vertex_index);
    }
  }

  // Generate faces
  for (int i = 0; i < num_faces_u; i++) {
    for (int j = 0; j < num_faces_v; j++) {
      const int face_index = i * num_faces_v + j;

      // Calculate vertex indices for this quad
      int v00 = i * num_vertices_v + j;
      int v01 = i * num_vertices_v + (j + 1);
      int v10 = (i + 1) * num_vertices_v + j;
      int v11 = (i + 1) * num_vertices_v + (j + 1);

      // Set face indices (winding order for outward normals)
      F(face_index, 0) = v00;
      F(face_index, 1) = v10;
      F(face_index, 2) = v11;
      F(face_index, 3) = v01;

      // UV and normal faces use same connectivity
      UF.row(face_index) = F.row(face_index);
      NF.row(face_index) = F.row(face_index);
    }
  }
}
