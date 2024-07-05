//
// Created by yarik on 28.03.24.
//
#include "negative.h"

void Negative::Apply(BMP &bmp) {
  Matrix<Pixel> &image = bmp.data_matrix;
  for (size_t i = 0; i < image.GetRowsNum(); ++i) {
    for (size_t j = 0; j < image.GetColsNum(); ++j) {
      Pixel &original = image[i][j];
      original.r =
          utils::UintFromDouble(1 - utils::DoubleFromUint8(original.r));
      original.b =
          utils::UintFromDouble(1 - utils::DoubleFromUint8(original.b));
      original.g =
          utils::UintFromDouble(1 - utils::DoubleFromUint8(original.g));
    }
  }
  std::cout << "negative has been applied" << std::endl;
}