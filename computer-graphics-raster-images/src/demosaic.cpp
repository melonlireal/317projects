#include "demosaic.h"

#include <iostream>
#include <ostream>
//
// int help_avg_lr(int i, int j, const int & width, const std::vector<unsigned char> & bayer);
// int help_avg_ud(int i, int j, const int & width, const int & height, const std::vector<unsigned char> & bayer);
// int help_avg_cor(int i, int j, const int & width, const int & height, const std::vector<unsigned char> & bayer);
// int help_avg_sid(int i, int j, const int & width, const int & height, const std::vector<unsigned char> & bayer);

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // for (int i = 0; i < height; i++) {
  //   for (int j = 0; j < width; j++) {
  //     if ((i%2 == 0 && j%2 == 0) || (i%2 == 1 && j%2 == 1)) { // this means green
  //       if (j%2 == 0) { //GBGBGB
  //         rgb[(i*height + j)*3] = bayer[i*width + j];
  //         rgb[(i*height + j)*3 + 2] = bayer[i*width + j];
  //       }else if (j%2 == 1) {//RBRBRB
  //         rgb[(i*height + j)*3] = bayer[i*width + j];
  //         rgb[(i*height + j)*3 + 2] = bayer[i*width + j];
  //       }
  //       rgb[(i*height + j)*3 + 1] = bayer[i*width + j]; //green
  //     }else if (i % 2 == 0 && j%2 == 1) { //blue
  //       rgb[(i*height + j)*3] = bayer[i*width + j];
  //       rgb[(i*height + j)*3 + 1] = bayer[i*width + j];
  //       rgb[(i*height + j)*3 + 2] = bayer[i*width + j]; //blue
  //     }else if (i  %2 == 1 && j % 2 == 0) { // red
  //       rgb[(i*height + j)*3] = bayer[i*width + j]; //red
  //       rgb[(i*height + j)*3 + 1] = bayer[i*width + j];
  //       rgb[(i*height + j)*3 + 2] = bayer[i*width + j];
  //     }
  //   }
  // }
  ////////////////////////////////////////////////////////////////////////////
}

// int help_avg_lr(
//   int i,
//   int j,
//   const int & width,
//   const std::vector<unsigned char> & bayer
//   ) { // help average left and right
//   if (j == 0) {
//     return bayer[i*width + j + 1];
//   }else if (j == width - 1) {
//     return  bayer[i*width + j - 1];
//   }else {
//     return (bayer[i*width + j - 1] + bayer[i*width + j + 1])/2;
//   }
// }

// int help_avg_ud(
// int i,
// int j,
// const int & width,
// const int & height,
// const std::vector<unsigned char> & bayer) { // help average up and down
// if(i == 0) {
//   return bayer[(i+1)*width + j];
// }else if (i == height - 1) {
//   return bayer[(i-1)*width + j];
// }else {
//   return (bayer[(i+1)*width + j] + bayer[(i-1)*width + j])/2;
// }
// }
//
// int help_avg_cor(
// int i,
// int j,
// const int & width,
// const int & height,
// const std::vector<unsigned char> & bayer) { // help average corner
// if (i == height -1 && j == 0) { // bottom left corner
//   return bayer[(i-1)*width + j + 1];
// }else if (i == 0 && j == width - 1){ //top right corner
//   return bayer[(i+1)*width + j - 1];
// }else if (i == 0) { // top row and not corner
//   return (bayer[(i+1)*width + j -1] + bayer[(i+1)*width + j + 1])/2;
// }else if (i == height -1) { // bottom row and not corner
//   return (bayer[(i-1)*width + j +1] + bayer[(i-1)*width + j - 1])/2;
// }else if (j == 0) { // first column but not coner
//   return (bayer[(i-1)*width + j+1] + bayer[(i+1)*width + j + 1])/2;
// }else if (j == width - 1) { // last column but not coner
//   return (bayer[(i-1)*width + j-1] + bayer[(i+1)*width+j-1])/2;
// }else {
//   return (bayer[(i-1)*width + j+1] + bayer[(i+1)*width + j + 1] + bayer[(i-1)*width + j-1] + bayer[(i+1)*width+j-1])/4;
// }
// }
//
// int help_avg_sid(
// int i,
// int j,
// const int & width,
// const int & height,
// const std::vector<unsigned char> & bayer) { //help average sides
//   if (i == height -1 && j == 0) { // bottom left corner
//     return (bayer[(i-1)*width + j] + bayer[i*width + j + 1])/2;
//   }else if (i == 0 && j == width - 1){ //top right corner
//     return (bayer[(i+1)*width + j] + bayer[i*width + j - 1])/2;
//   }else if (i == 0) { // top row and not corner
//     return (bayer[i*width + j + 1] + bayer[i*width + j - 1] + bayer[(i+1)*width+j])/3;
//   }else if (i == height -1) { // bottom row and not corner
//     return (bayer[i*width + j + 1] + bayer[i*width + j - 1] + bayer[(i-1)*width+j])/3;
//   }else if (j == 0) { // first column but not coner
//     return (bayer[i*width + j + 1] + bayer[(i+1)*width + j] + bayer[(i-1)*width + j])/3;
//   }else if (j == width - 1) { // last column but not coner
//     return (bayer[i*width + j - 1] + bayer[(i+1)*width + j] + bayer[(i-1)*width + j])/3;
//   }else {
//     return (bayer[(i-1)*width + j] + bayer[(i+1)*width + j] + bayer[i*width+j - 1] + bayer[i*width+j+1])/4;
//   }
// }
