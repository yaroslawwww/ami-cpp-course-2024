//
// Created by yarik on 26.03.24.
//

#ifndef GRAPHICSSNIPPETS_NEGATIVE_H
#define GRAPHICSSNIPPETS_NEGATIVE_H

#include "../bmp.h"
#include "base_filter.h"
#include <iostream>

class Negative : public Filter {
  void Apply(BMP &bmp) override;

public:
  explicit Negative() = default;
};

#endif // GRAPHICSSNIPPETS_NEGATIVE_H
