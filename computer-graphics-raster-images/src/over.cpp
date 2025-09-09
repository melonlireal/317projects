#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  for (int i = 0; i < width*height; i ++) {
    if (B[i*4+3] == 0 ) { // if nether or only dest, transparent
      C[i*4] = (unsigned char)0;
      C[i*4+1] = (unsigned char)0;
      C[i*4+2] = (unsigned char)0;
      C[i*4+3] = (unsigned char)0;
    }else if (B[i*4+3] != 0 && A[i*4+3] != 0 ) { // if both, use dest
      C[i*4] = A[i*4];
      C[i*4+1] = A[i*4+1];
      C[i*4+2] = A[i*4+2];
      C[i*4+3] = A[i*4+3];
    }else if (B[i*4+3] != 0 && A[i*4+3] == 0) { // if only source, use source
      C[i*4] = B[i*4];
      C[i*4+1] = B[i*4+1];
      C[i*4+2] = B[i*4+2];
      C[i*4+3] = B[i*4+3];
    }
  }
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
}
