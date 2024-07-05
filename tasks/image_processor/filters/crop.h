//
// Created by yarik on 26.03.24.
//

#ifndef GRAPHICSSNIPPETS_CROP_H
#define GRAPHICSSNIPPETS_CROP_H

#include "../bmp.h"
#include "base_filter.h"
#include <iostream>

struct Crop : Filter {
  void Apply(BMP &bmp) override;

  explicit Crop(int param1, int param2);

private:
  int param1_;
  int param2_;
};

#endif // GRAPHICSSNIPPETS_CROP_H
