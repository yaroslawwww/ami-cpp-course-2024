//
// Created by yarik on 28.03.24.
//
#include "grayscale.h"

void GrayScale::Apply(BMP &bmp) {
  const double para_m1_gs = 0.299;
  const double para_m2_gs = 0.587;
  const double para_m3_gs = 0.114;
  Matrix<Pixel> &image = bmp.data_matrix;
  for (size_t i = 0; i < image.GetRowsNum(); ++i) {
    for (size_t j = 0; j < image.GetColsNum(); ++j) {
      Pixel &original = image[i][j];
      double x = para_m1_gs * utils::DoubleFromUint8(original.r) +
                 para_m2_gs * utils::DoubleFromUint8(original.g) +
                 para_m3_gs * utils::DoubleFromUint8(original.b);
      original.r = utils::UintFromDouble(x);
      original.b = utils::UintFromDouble(x);
      original.g = utils::UintFromDouble(x);
    }
  }
  std::cout << "grayscale has been applied" << std::endl;
}