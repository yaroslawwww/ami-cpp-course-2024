//
// Created by yarik on 27.03.24.
//

#ifndef GRAPHICSSNIPPETS_GRAYSCALE_H
#define GRAPHICSSNIPPETS_GRAYSCALE_H

#include "../bmp.h"
#include "base_filter.h"
#include <iostream>

struct GrayScale : Filter {
  void Apply(BMP &bmp) override;

  explicit GrayScale() = default;
};

#endif // GRAPHICSSNIPPETS_GRAYSCALE_H
