//
// Created by yarik on 26.03.24.
//

#ifndef GRAPHICSSNIPPETS_EDGE_H
#define GRAPHICSSNIPPETS_EDGE_H

#include "../bmp.h"
#include "base_filter.h"
#include "grayscale.h"
#include <iostream>
#include <string>

struct EdgeDetection : GrayScale {
  void Apply(BMP &bmp) override;

  explicit EdgeDetection(double param) : GrayScale(), threshold(param){};

public:
  double threshold;
};

#endif // GRAPHICSSNIPPETS_EDGE_H
