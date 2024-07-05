//
// Created by yarik on 25.03.24.
//
#include "base_filter.h"

void MatrixCopyWithOffset(Matrix<Pixel> &whole_matrix,
                          Matrix<Pixel> &new_matrix, uint row_offset,
                          uint col_offset) {
  for (size_t i = 0; i < new_matrix.GetRowsNum(); ++i) {
    for (size_t j = 0; j < new_matrix.GetColsNum(); ++j) {
      new_matrix[i][j] = whole_matrix[i + row_offset][j + col_offset];
    }
  }
}

double utils::DoubleFromUint8(uint8_t color) {
  return static_cast<double>(color) / static_cast<double>(max_pixel_value);
}

uint8_t utils::UintFromDouble(double color) {
  return static_cast<uint8_t>(color * static_cast<double>(max_pixel_value));
}

void ExtendBounds(Matrix<Pixel> &data, Matrix<Pixel> &image) {
  size_t rows_im = image.GetRowsNum() - 1;
  size_t cols_im = image.GetColsNum() - 1;
  for (size_t i = 0; i < rows_im + 1; ++i) {
    for (size_t j = 0; j < cols_im + 1; ++j) {
      data[i + 1][j + 1] = image[i][j];
    }
  }
  for (size_t i = 0; i < rows_im + 1; ++i) {
    data[i + 1][0] = image[i][0];
  }
  for (size_t j = 0; j < cols_im + 1; ++j) {
    data[0][j + 1] = image[0][j];
  }
  for (size_t i = 0; i < rows_im + 1; ++i) {
    data[i + 1][cols_im + 2] = image[i][cols_im];
  }
  for (size_t j = 0; j < cols_im + 1; ++j) {
    data[rows_im + 2][j + 1] = image[rows_im][j];
  }
  data[0][0] = image[0][0];
  data[rows_im + 2][cols_im + 2] = image[rows_im][cols_im];
  data[0][cols_im + 2] = image[0][cols_im];
  data[rows_im + 2][0] = image[rows_im][0];
}

void ApplyMatrixToPixel(Matrix<Pixel> &image, Matrix<Pixel> &extended_image,
                        Matrix<int> &filter_matrix, size_t row, size_t col) {
  image[row][col].r = image[row][col].g = image[row][col].b = 0;
  int r = 0;
  int g = 0;
  int b = 0;
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      r += static_cast<int>(extended_image[i + row][j + col].r) *
           filter_matrix[i][j];
      b += static_cast<int>(extended_image[i + row][j + col].b) *
           filter_matrix[i][j];
      g += static_cast<int>(extended_image[i + row][j + col].g) *
           filter_matrix[i][j];
    }
  }
  image[row][col].r = utils::UintFromDouble(
      std::min(1.0, static_cast<double>(std::max(0, r)) /
                        static_cast<double>(max_pixel_value)));
  image[row][col].g = utils::UintFromDouble(
      std::min(1.0, static_cast<double>(std::max(0, g)) /
                        static_cast<double>(max_pixel_value)));
  image[row][col].b = utils::UintFromDouble(
      std::min(1.0, static_cast<double>(std::max(0, b)) /
                        static_cast<double>(max_pixel_value)));
}
