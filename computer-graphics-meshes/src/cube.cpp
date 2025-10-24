#include "cube.h"

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////
  V.resize(8, 3);
  V << 0, 0, 0,  // 0: back-bottom-left
       1, 0, 0,  // 1: back-bottom-right
       1, 1, 0,  // 2: back-top-right
       0, 1, 0,  // 3: back-top-left
       0, 0, 1,  // 4: front-bottom-left
       1, 0, 1,  // 5: front-bottom-right
       1, 1, 1,  // 6: front-top-right
       0, 1, 1;  // 7: front-top-left

  F.resize(6, 4);
  F << 1, 5, 6, 2,  // right face
       4, 0, 3, 7,  // left face
       0, 4, 5, 1,  // bottom face - OPTION 2A
       2, 6, 7, 3,  // top face - OPTION 2B
       5, 4, 7, 6,  // front face
       0, 1, 2, 3;  // back face

  // UV coordinates for texture mapping - each face maps to one color square
  UV.resize(24, 2);  // 6 faces × 4 vertices per face

  // (0,0.25), (0.25,0), (0.25,0.25), (0.25,0.5), (0.5,0.25), (0.75,0.25)

  // maps to square at (0.5,0.25)
  UV.row(0) << 0.5, 0.25;    // bottom-left
  UV.row(1) << 0.75, 0.25;   // bottom-right
  UV.row(2) << 0.75, 0.5;    // top-right
  UV.row(3) << 0.5, 0.5;     // top-left

  // maps to square at (0,0.25)
  UV.row(4) << 0.0, 0.25;    // bottom-left
  UV.row(5) << 0.25, 0.25;   // bottom-right
  UV.row(6) << 0.25, 0.5;    // top-right
  UV.row(7) << 0.0, 0.5;     // top-left

  // maps to square at (0.25,0)
  UV.row(8) << 1 - 0.25, 0.0;    // front-left vertex (4)
  UV.row(9) << 1 - 0.5, 0.0;     // front-right vertex (5)
  UV.row(10) << 1- 0.5, 0.25;   // back-right vertex (1)
  UV.row(11) << 1 - 0.25, 0.25;  // back-left vertex (0)

  // maps to square at (0.25,0.5)
  UV.row(12) << 1 - 0.25, 0.5;   // back-left vertex (3)
  UV.row(13) << 1 - 0.5, 0.5;    // back-right vertex (2)
  UV.row(14) << 1 - 0.5, 0.75;   // front-right vertex (6)
  UV.row(15) << 1 - 0.25, 0.75;  // front-left vertex (7)

  // maps to square at (0.25,0.25)
  UV.row(16) << 0.25, 0.25;  // bottom-left
  UV.row(17) << 0.5, 0.25;   // bottom-right
  UV.row(18) << 0.5, 0.5;    // top-right
  UV.row(19) << 0.25, 0.5;   // top-left

  // maps to square at (0.75,0.25)
  UV.row(20) << 0.75, 0.25;  // bottom-left
  UV.row(21) << 1.0, 0.25;   // bottom-right
  UV.row(22) << 1.0, 0.5;    // top-right
  UV.row(23) << 0.75, 0.5;   // top-left

  // UV indices
  UF.resize(6, 4);
  UF << 0, 1, 2, 3,     // right face
        4, 5, 6, 7,     // left face
        8, 9, 10, 11,   // bottom face (maps to (0.25,0) square)
        12, 13, 14, 15, // top face (maps to (0.25,0.5) square)
        16, 17, 18, 19, // front face
        20, 21, 22, 23; // back face

  // Normals
  NV.resize(6, 3);
  NV << 1, 0, 0,   // right face normal (points +X)
       -1, 0, 0,   // left face normal (points -X)
        0, -1, 0,  // bottom face normal (points -Y)
        0, 1, 0,   // top face normal (points +Y)
        0, 0, 1,   // front face normal (points +Z)
        0, 0, -1;  // back face normal (points -Z)

  // Normal indices
  NF.resize(6, 4);
  NF << 0, 0, 0, 0,  // right face uses normal 0
        1, 1, 1, 1,  // left face uses normal 1
        2, 2, 2, 2,  // bottom face uses normal 2
        3, 3, 3, 3,  // top face uses normal 3
        4, 4, 4, 4,  // front face uses normal 4
        5, 5, 5, 5;  // back face uses normal 5
}
