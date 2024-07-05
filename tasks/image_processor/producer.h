//
// Created by yarik on 27.03.24.
//

#ifndef GRAPHICSSNIPPETS_PRODUCER_H
#define GRAPHICSSNIPPETS_PRODUCER_H

#include "cmdlineparser.h"
#include "filters/base_filter.h"
#include "filters/blur.h"
#include "filters/crop.h"
#include "filters/edge.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/sharpening.h"
#include <map>
#include <stdexcept>

Filter *CropFilterMaker(const FilterDescriptor &fd);

Filter *NegativefilterMaker(const FilterDescriptor &fd);

Filter *GrayscaleFilterMaker(const FilterDescriptor &fd);

Filter *EdgeDetectionFilterMaker(const FilterDescriptor &fd);

Filter *SharpeningFilterMaker(const FilterDescriptor &fd);

struct FiltersProducers {
  using PFilterProducer = Filter *(*)(const FilterDescriptor &fd);
  std::map<std::string, PFilterProducer> filter_producers_;

  PFilterProducer Find(std::map<std::string, PFilterProducer> &filter_producers,
                       const std::string &filter_name) const;

  FiltersProducers();
};

#endif // GRAPHICSSNIPPETS_PRODUCER_H
