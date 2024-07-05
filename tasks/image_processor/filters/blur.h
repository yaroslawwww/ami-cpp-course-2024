//
// Created by yarik on 26.03.24.
//

#ifndef GRAPHICSSNIPPETS_BLUR_H
#define GRAPHICSSNIPPETS_BLUR_H

#include "base_filter.h"

struct Blur : public Filter {
  void Apply(BMP &bmp) override;

  explicit Blur(double sigma) : sigma_(sigma){};

private:
  double sigma_;
};
void HorizontalBlur(Matrix<Pixel> &image, Matrix<Pixel> &new_image,
                    double sigma);
#endif // GRAPHICSSNIPPETS_BLUR_H
