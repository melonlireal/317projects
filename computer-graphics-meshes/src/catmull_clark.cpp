#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  SV = V;
  SF = F;

  // Current vertices and faces for iteration
  Eigen::MatrixXd current_V = V;
  Eigen::MatrixXi current_F = F;

  for (int i = 0; i < num_iters; i++) {
    const int nV = current_V.rows();
    const int nF = current_F.rows();

    // Step 1: Compute face points (average of face vertices)
    Eigen::MatrixXd face_points(nF, 3);
    for (int j = 0; j < nF; j++) {
      face_points.row(j) = (current_V.row(current_F(j, 0)) +
                           current_V.row(current_F(j, 1)) +
                           current_V.row(current_F(j, 2)) +
                           current_V.row(current_F(j, 3))) / 4.0;
    }

    // Step 2: Compute edge points
    // Use a map to store edge points (key: sorted vertex indices)
    std::unordered_map<std::string, Eigen::RowVector3d> edge_point_map;
    std::unordered_map<std::string, std::vector<int>> edge_face_adjacency;

    // Build edge-face adjacency
    for (int k = 0; k < nF; k++) {
      for (int j = 0; j < 4; j++) {
        int v1 = current_F(k, j);
        int v2 = current_F(k, (j + 1) % 4);

        // Create sorted key for edge
        std::string key = std::to_string(std::min(v1, v2)) + "," +
                         std::to_string(std::max(v1, v2));

        edge_face_adjacency[key].push_back(k);
      }
    }

    // Compute edge points
    std::vector<Eigen::RowVector3d> edge_points;
    std::unordered_map<std::string, int> edge_point_index;
    int edge_counter = 0;

    for (const auto& entry : edge_face_adjacency) {
      const std::string& key = entry.first;
      const std::vector<int>& faces = entry.second;

      // Extract vertices from key
      size_t comma_pos = key.find(',');
      int v1 = std::stoi(key.substr(0, comma_pos));
      int v2 = std::stoi(key.substr(comma_pos + 1));

      Eigen::RowVector3d edge_point;

      if (faces.size() == 2) {
        // Internal edge: average of endpoints and adjacent face points
        edge_point = (current_V.row(v1) + current_V.row(v2) +
                     face_points.row(faces[0]) + face_points.row(faces[1])) / 4.0;
      } else {
        // Boundary edge: average of endpoints only
        edge_point = (current_V.row(v1) + current_V.row(v2)) / 2.0;
      }

      edge_points.push_back(edge_point);
      edge_point_index[key] = edge_counter++;
    }

    // Step 3: Update original vertices
    Eigen::MatrixXd updated_vertices(nV, 3);

    // Build vertex-face and vertex-vertex adjacency
    std::vector<std::vector<int>> vertex_faces(nV);
    std::vector<std::vector<int>> vertex_vertices(nV);

    for (int i = 0; i < nF; i++) {
      for (int j = 0; j < 4; j++) {
        int vertex = current_F(i, j);
        vertex_faces[vertex].push_back(i);

        // Add neighboring vertices
        int prev_vertex = current_F(i, (j + 3) % 4);
        int next_vertex = current_F(i, (j + 1) % 4);
        vertex_vertices[vertex].push_back(prev_vertex);
        vertex_vertices[vertex].push_back(next_vertex);
      }
    }

    // Remove duplicates from vertex_vertices
    for (int i = 0; i < nV; i++) {
      std::sort(vertex_vertices[i].begin(), vertex_vertices[i].end());
      vertex_vertices[i].erase(
        std::unique(vertex_vertices[i].begin(), vertex_vertices[i].end()),
        vertex_vertices[i].end());
    }

    // Update each original vertex
    for (int i = 0; i < nV; i++) {
      const int n = vertex_faces[i].size(); // valence

      if (n == 0) continue;

      // F: average of adjacent face points
      Eigen::RowVector3d F_point = Eigen::RowVector3d::Zero();
      for (int face_idx : vertex_faces[i]) {
        F_point += face_points.row(face_idx);
      }
      F_point /= n;

      // R: average of edge midpoints
      Eigen::RowVector3d R_point = Eigen::RowVector3d::Zero();
      for (int neighbor : vertex_vertices[i]) {
        R_point += (current_V.row(i) + current_V.row(neighbor)) / 2.0;
      }
      R_point /= n;

      // P: original vertex position
      Eigen::RowVector3d P_point = current_V.row(i);

      // New position formula: F + 2R + (n-3)P
      updated_vertices.row(i) = (F_point + 2.0 * R_point + (n - 3.0) * P_point) / n;
    }

    // Step 4: Create new vertex list
    const int nE = edge_points.size();
    SV.resize(nV + nF + nE, 3);

    // Original vertices (updated)
    SV.block(0, 0, nV, 3) = updated_vertices;

    // Face points
    SV.block(nV, 0, nF, 3) = face_points;

    // Edge points
    for (int i = 0; i < nE; i++) {
      SV.row(nV + nF + i) = edge_points[i];
    }

    // Step 5: Create new faces
    SF.resize(4 * nF, 4);

    for (int i = 0; i < nF; i++) {
      int v0 = current_F(i, 0);
      int v1 = current_F(i, 1);
      int v2 = current_F(i, 2);
      int v3 = current_F(i, 3);

      // Get edge point indices
      int e0 = edge_point_index[std::to_string(std::min(v0, v1)) + "," +
                              std::to_string(std::max(v0, v1))];
      int e1 = edge_point_index[std::to_string(std::min(v1, v2)) + "," +
                              std::to_string(std::max(v1, v2))];
      int e2 = edge_point_index[std::to_string(std::min(v2, v3)) + "," +
                              std::to_string(std::max(v2, v3))];
      int e3 = edge_point_index[std::to_string(std::min(v3, v0)) + "," +
                              std::to_string(std::max(v3, v0))];

      // Face point index
      int f = nV + i;

      // Edge point indices in new vertex array
      int ep0 = nV + nF + e0;
      int ep1 = nV + nF + e1;
      int ep2 = nV + nF + e2;
      int ep3 = nV + nF + e3;

      // Create 4 new quads
      SF.row(4 * i + 0) = Eigen::RowVector4i(v0, ep0, f, ep3);
      SF.row(4 * i + 1) = Eigen::RowVector4i(v1, ep1, f, ep0);
      SF.row(4 * i + 2) = Eigen::RowVector4i(v2, ep2, f, ep1);
      SF.row(4 * i + 3) = Eigen::RowVector4i(v3, ep3, f, ep2);
    }

    // Prepare for next iteration
    current_V = SV;
    current_F = SF;
  }
  ////////////////////////////////////////////////////////////////////////////
}
