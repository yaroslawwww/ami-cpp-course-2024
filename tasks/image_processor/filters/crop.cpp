//
// Created by yarik on 28.03.24.
//
#include "crop.h"

void Crop::Apply(BMP &bmp) {
  if (param1_ > bmp.bmp_info_header.BMP_height) {
    param1_ = bmp.bmp_info_header.BMP_height;
  }
  if (param2_ > bmp.bmp_info_header.BMP_width) {
    param2_ = bmp.bmp_info_header.BMP_width;
  }
  Matrix<Pixel> new_image = Matrix<Pixel>(param1_, param2_);
  MatrixCopyWithOffset(bmp.data_matrix, new_image, 0, 0);
  bmp.data_matrix = new_image;
  bmp.bmp_header.bytes_size = sizeof(bmp.bmp_header) +
                              sizeof(bmp.bmp_info_header) +
                              param1_ * param2_ * 3 * sizeof(uint8_t);
  bmp.bmp_info_header.BMP_height = param1_;
  bmp.bmp_info_header.BMP_width = param2_;
  std::cout << "crop has been applied" << std::endl;
}

Crop::Crop(int param1, int param2) {
  param1_ = param1;
  param2_ = param2;
}