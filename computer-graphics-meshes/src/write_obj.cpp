#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::ofstream obj(filename);

  if (obj.is_open()) {
    for (int i = 0; i < V.rows(); i++) {
      obj << "v " << V(i,0) << " " << V(i,1) << " " << V(i,2) << std::endl;
    }
    for (int i = 0; i < UV.rows(); i++) {
      obj << "vt " << UV(i,0) << " " << UV(i,1) << std::endl;
    }
    for (int i = 0; i < NV.rows(); i++) {
      obj << "vn " << NV(i,0) << " " << NV(i,1) << " " << NV(i,2) << std::endl;
    }
    for (int i = 0; i < F.rows(); i++) {
      obj << "f";
      for (int j = 0; j < F.cols(); j++) {
        obj << " " << (F(i,j) + 1); // Convert to 1-based index
        if (UV.rows() > 0 || NV.rows() > 0) {
          obj << "/";
          if (UV.rows() > 0) {
            obj << (UF(i,j) + 1); // Convert to 1-based index
          }
          if (NV.rows() > 0) {
            obj << "/" << (NF(i,j) + 1); // Convert to 1-based index
          }
        }
      }
      obj << std::endl;
    }
    obj.close();
    return true;
  }
  ////////////////////////////////////////////////////////////////////////////
  return false;
}
