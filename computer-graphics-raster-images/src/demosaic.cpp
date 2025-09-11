#include "demosaic.h"

#include <iostream>
#include <ostream>


void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if ((i%2 == 0 && j%2 == 0) || (i%2 == 1 && j%2 == 1)) {// this means green
          if (i%2 == 0) {// on GBGBGB row
            //for blue avg
            if (j == 0) {// if on first col
              rgb[(i * width + j)*3 + 2] = bayer[(i * width + j) + 1];
            }else {
              rgb[(i * width + j)*3 + 2] = (bayer[(i * width + j) + 1] + bayer[(i * width + j) - 1])/2;
            }
            //for red avg
            if (i == 0) {// if on first row
              rgb[(i * width + j)*3] = bayer[((i+1) * width + j)];
            }else {
              rgb[(i * width + j)*3] = (bayer[((i+1) * width + j)] + bayer[((i-1) * width + j)])/2;
            }

          }else if (i%2 == 1) {// on RGRGRG row
            //for blue avg
            if (i == height -1) {// if on last col
              rgb[(i * width + j)*3 + 2] = bayer[((i-1) * width + j)];
            }else {
              rgb[(i * width + j)*3 + 2] = (bayer[((i-1) * width + j)] + bayer[((i+1) * width + j)])/2;
            }
            //for red avg
            if (j == width - 1) {// if on last col
              rgb[(i * width + j)*3] = bayer[(i * width + j -1)];
            }else {
              rgb[(i * width + j)*3] = (bayer[(i * width + j -1)] + bayer[(i * width + j + 1)])/2;
            }

          }
        // for green
        rgb[(i * width + j)*3 + 1] = bayer[(i * width + j)];

      }else if (i%2 == 0 && j%2 == 1) { //blue

        if (i == 0 && j == width - 1) { //top right corner

          rgb[(i * width + j)*3] = bayer[((i+1) * width + j - 1)]; //red
          rgb[(i * width + j)*3 + 1] = (bayer[((i+1) * width + j)] + bayer[(i * width + j - 1)])/2; //green

        }else if (i == 0) { // first row

          rgb[(i * width + j)*3] = (bayer[((i+1) * width + j - 1)] + bayer[((i+1) * width + j + 1)])/2; //red
          rgb[(i * width + j)*3 + 1] = (bayer[((i+1) * width + j)] + bayer[(i * width + j + 1)] + bayer[(i * width + j - 1)])/3; //green

        }else if (j == width - 1) { //last col

          rgb[(i * width + j)*3] = (bayer[((i-1) * width + j - 1)] + bayer[((i+1) * width + j - 1)])/2;//red
          rgb[(i * width + j)*3 + 1] = (bayer[((i+1) * width + j)] + bayer[((i-1) * width + j)] + bayer[(i * width + j - 1)])/3; //green

        }else { //normal

          rgb[(i * width + j)*3] = (bayer[((i-1) * width + j - 1)] + bayer[((i-1) * width + j + 1)] + \
            bayer[((i+1) * width + j - 1)] + bayer[((i+1) * width + j + 1)])/4;//red
          rgb[(i * width + j)*3 + 1] = (bayer[((i+1) * width + j)] + bayer[((i-1) * width + j)] \
            + bayer[(i * width + j - 1)] + + bayer[(i * width + j + 1)])/4; //green

        }
        rgb[(i*width+j)*3 + 2] = bayer[(i * width + j)]; // blue

      }else if (i%2 == 1 && j%2 == 0) { // red
        if (i == height -1 && j == 0) {// bottom left corner

          rgb[(i * width + j)*3 + 1] = (bayer[(i * width + j + 1)] + bayer[((i-1) * width + j)])/2; //green
          rgb[(i * width + j)*3 + 2] = bayer[((i-1) * width + j + 1)]; //blue

        }else if (j == 0) { //first col

          rgb[(i * width + j)*3 + 1] = (bayer[(i * width + j + 1)] + bayer[((i-1) * width + j)] + bayer[((i+1) * width + j)])/3; //green
          rgb[(i * width + j)*3 + 2] = (bayer[((i-1) * width + j + 1)] + bayer[((i+1) * width + j + 1)])/2; //blue

        }else if (i == height - 1) { //last row

          rgb[(i * width + j)*3 + 1] = (bayer[(i * width + j + 1)] + bayer[(i * width + j -1)] + bayer[((i-1) * width + j)])/3;//green
          rgb[(i * width + j)*3 + 2] = (bayer[((i-1) * width + j + 1)] + bayer[((i-1) * width + j - 1)])/2; //blue

        }else { //normal;
          rgb[(i * width + j)*3 + 1] = (bayer[(i * width + j + 1)] + bayer[(i * width + j -1)] + \
            bayer[((i-1) * width + j)] + bayer[((i+1) * width + j)])/4;//green
          rgb[(i * width + j)*3 + 2] = (bayer[((i-1) * width + j + 1)] + bayer[((i-1) * width + j - 1)]+ \
            bayer[((i+1) * width + j + 1)] + bayer[((i+1) * width + j - 1)])/4; //blue
        }
        rgb[(i * width + j)*3] = bayer[(i * width + j)];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}