//
// Created by yarik on 25.03.24.
//

#ifndef GRAPHICSSNIPPETS_BASE_FILTER_H
#define GRAPHICSSNIPPETS_BASE_FILTER_H

#include "../bmp.h"
#include <vector>

void MatrixCopyWithOffset(Matrix<Pixel> &whole_matrix,
                          Matrix<Pixel> &new_matrix, uint row_offset,
                          uint col_offset);

class Filter {
public:
  virtual void Apply(BMP &bmp) = 0;

  virtual ~Filter(){};
};

enum constants : const uint8_t { max_pixel_value = 255 };
namespace utils {
double DoubleFromUint8(uint8_t color);

uint8_t UintFromDouble(double color);
} // namespace utils

void ExtendBounds(Matrix<Pixel> &data, Matrix<Pixel> &image);

void ApplyMatrixToPixel(Matrix<Pixel> &image, Matrix<Pixel> &extended_image,
                        Matrix<int> &filter_matrix, size_t row, size_t col);

#endif // GRAPHICSSNIPPETS_BASE_FILTER_H
