//
// Created by yarik on 26.03.24.
//

#ifndef GRAPHICSSNIPPETS_SHARPENING_H
#define GRAPHICSSNIPPETS_SHARPENING_H

#include "../bmp.h"
#include "base_filter.h"
#include <iostream>

struct Sharpening : Filter {
  void Apply(BMP &bmp) override;

  explicit Sharpening() = default;
};

#endif // GRAPHICSSNIPPETS_SHARPENING_H
