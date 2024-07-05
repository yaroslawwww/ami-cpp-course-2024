//
// Created by yarik on 28.03.24.
//
#include "edge.h"

Matrix<int> &CreateEdgeMatrix(Matrix<int> &filter_matrix) {
  const int sharpening_matrix_central_element = 4;
  const int sharpening_matrix_side_elements = -1;
  filter_matrix[0][1] = filter_matrix[1][0] = filter_matrix[2][1] =
      filter_matrix[1][2] = sharpening_matrix_side_elements;
  filter_matrix[1][1] = sharpening_matrix_central_element;
  filter_matrix[0][1] = filter_matrix[1][0] = filter_matrix[2][1] =
      filter_matrix[1][2] = -1;
  filter_matrix[1][1] = 4;
  return filter_matrix;
}

void CheckThreshold(Matrix<Pixel> &image, double threshold, size_t i,
                    size_t j) {
  if (image[i][j].r > threshold * static_cast<double>(max_pixel_value)) {
    image[i][j].r = max_pixel_value;
    image[i][j].g = max_pixel_value;
    image[i][j].b = max_pixel_value;
  } else {
    image[i][j].r = 0;
    image[i][j].g = 0;
    image[i][j].b = 0;
  }
}

void EdgeDetection::Apply(BMP &bmp) {
  Matrix<int> filter_matrix = Matrix<int>(3, 3);
  filter_matrix = CreateEdgeMatrix(filter_matrix);
  GrayScale::Apply(bmp);
  Matrix<Pixel> &image = bmp.data_matrix;
  size_t rows = image.GetRowsNum();
  size_t cols = image.GetColsNum();
  Matrix<Pixel> data = Matrix<Pixel>(rows + 2, cols + 2);
  ExtendBounds(data, image);
  for (size_t i = 0; i < image.GetRowsNum(); ++i) {
    for (size_t j = 0; j < image.GetColsNum(); ++j) {
      ApplyMatrixToPixel(image, data, filter_matrix, i, j);
    }
  }
  for (size_t i = 0; i < image.GetRowsNum(); ++i) {
    for (size_t j = 0; j < image.GetColsNum(); ++j) {
      CheckThreshold(image, threshold, i, j);
    }
  }
  std::cout << "edge has been applied" << std::endl;
}