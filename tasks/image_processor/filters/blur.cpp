//
// Created by yarik on 28.03.24.
//
#include "blur.h"
#include <cmath>
#include <iostream>

namespace leap_c {
const double PI = M_PI;
const double E = M_E;
} // namespace leap_c

double ExpPower(size_t i, size_t j, double radius) {
  return pow(leap_c::E,
             -pow(abs(static_cast<int>(j) - static_cast<int>(i)), 2) /
                 (2 * pow(radius, 2)));
}

void HorizontalGaussianFunctionPixel(Matrix<Pixel> &image,
                                     Matrix<Pixel> &new_image,
                                     size_t number_of_row, size_t elem,
                                     double radius) {
  double r = 0;
  double g = 0;
  double b = 0;
  for (size_t i = 0; i < image[number_of_row].Size(); ++i) {
    r += utils::DoubleFromUint8(image[number_of_row][i].r) * 1 /
         (2 * leap_c::PI * pow(radius, 2)) * ExpPower(elem, i, radius);
    g += utils::DoubleFromUint8(image[number_of_row][i].g) * 1 /
         (2 * leap_c::PI * pow(radius, 2)) * ExpPower(elem, i, radius);
    b += utils::DoubleFromUint8(image[number_of_row][i].b) * 1 /
         (2 * leap_c::PI * pow(radius, 2)) * ExpPower(elem, i, radius);
  }
  Pixel pixel;
  pixel.r = utils::UintFromDouble(r);
  pixel.g = utils::UintFromDouble(g);
  pixel.b = utils::UintFromDouble(b);
  new_image[number_of_row][elem] = pixel;
}

void HorizontalBlur(Matrix<Pixel> &image, Matrix<Pixel> &new_image,
                    double sigma) {
  for (size_t i = 0; i < image.GetRowsNum(); ++i) {
    for (size_t j = 0; j < image.GetColsNum(); ++j) {
      HorizontalGaussianFunctionPixel(image, new_image, i, j, sigma);
    }
  }
}
void VerticalGaussianFunctionPixel(Matrix<Pixel> &image,
                                   Matrix<Pixel> &new_image,
                                   size_t number_of_col, size_t elem,
                                   double radius) {
  double r = 0;
  double g = 0;
  double b = 0;
  for (size_t i = 0; i < image(number_of_col).Size(); ++i) {
    r += utils::DoubleFromUint8(image(number_of_col)(i).r) * 1 /
         (2 * leap_c::PI * pow(radius, 2)) * ExpPower(elem, i, radius);
    g += utils::DoubleFromUint8(image(number_of_col)(i).g) * 1 /
         (2 * leap_c::PI * pow(radius, 2)) * ExpPower(elem, i, radius);
    b += utils::DoubleFromUint8(image(number_of_col)(i).b) * 1 /
         (2 * leap_c::PI * pow(radius, 2)) * ExpPower(elem, i, radius);
  }
  Pixel pixel;
  pixel.r = utils::UintFromDouble(r);
  pixel.g = utils::UintFromDouble(g);
  pixel.b = utils::UintFromDouble(b);
  new_image(number_of_col)(elem) = pixel;
}

void VerticalBlur(Matrix<Pixel> &image, Matrix<Pixel> &new_image,
                  double sigma) {
  for (size_t i = 0; i < image.GetColsNum(); ++i) {
    for (size_t j = 0; j < image.GetRowsNum(); ++j) {
      VerticalGaussianFunctionPixel(image, new_image, i, j, sigma);
    }
  }
}
void Blur::Apply(BMP &bmp) {
  Matrix<Pixel> &image = bmp.data_matrix;
  Matrix<Pixel> new_image = image;
  for (size_t i = 0; i < image.GetRowsNum(); ++i) {
    HorizontalBlur(image, new_image, sigma_);
  }
  image = new_image;
  for (size_t i = 0; i < image.GetColsNum(); ++i) {
    VerticalBlur(image, new_image, sigma_);
  }
  image = new_image;
}
