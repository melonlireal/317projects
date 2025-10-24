#include "vertex_triangle_adjacency.h"

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);

  // Iterate through all faces
  for (int i = 0; i < F.rows(); i++) {
    // Each triangle has 3 vertices
    for (int corner = 0; corner < 3; corner++) {
      int vertex_index = F(i, corner);
      // Add this face to the vertex's adjacency list
      VF[vertex_index].push_back(i);
    }
  }
}

