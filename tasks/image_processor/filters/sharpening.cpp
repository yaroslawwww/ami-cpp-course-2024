//
// Created by yarik on 28.03.24.
//
#include "sharpening.h"

void Sharpening::Apply(BMP &bmp) {
  const int sharpening_matrix_central_element = 5;
  const int sharpening_matrix_side_elements = -1;
  Matrix<Pixel> &image = bmp.data_matrix;
  Matrix<int> filter_matrix(3, 3);
  filter_matrix[0][1] = filter_matrix[1][0] = filter_matrix[2][1] =
      filter_matrix[1][2] = sharpening_matrix_side_elements;
  filter_matrix[1][1] = sharpening_matrix_central_element;
  size_t rows = image.GetRowsNum();
  size_t cols = image.GetColsNum();
  Matrix<Pixel> data = Matrix<Pixel>(rows + 2, cols + 2);
  ExtendBounds(data, image);
  for (size_t i = 0; i < image.GetRowsNum(); ++i) {
    for (size_t j = 0; j < image.GetColsNum(); ++j) {
      ApplyMatrixToPixel(image, data, filter_matrix, i, j);
    }
  }
  std::cout << "sharpening has been applied" << std::endl;
}