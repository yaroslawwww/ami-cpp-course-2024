

#include "producer.h"

Filter *CropFilterMaker(const FilterDescriptor &fd) {
  if (fd.GetFilterParams().size() < 2) {
    throw std::logic_error("unfortuantely,crop filter can't be created.");
  }
  int new_height = std::stoi(fd.GetFilterParams()[0]);
  int new_width = std::stoi(fd.GetFilterParams()[1]);
  if (!new_width || !new_height) {
    std::logic_error("incorrect value for crop filter");
  }
  Crop *new_filter = new Crop(new_height, new_width);
  return new_filter;
}

Filter *NegativefilterMaker(const FilterDescriptor &fd) {
  Negative *new_filter = new Negative();
  return new_filter;
}

Filter *GrayscaleFilterMaker(const FilterDescriptor &fd) {
  GrayScale *new_filter = new GrayScale();
  return new_filter;
}

Filter *EdgeDetectionFilterMaker(const FilterDescriptor &fd) {
  if (fd.GetFilterParams().empty()) {
    throw std::logic_error(
        "unfortunately,edgedetection filter can't be created.");
  }
  double threshold = std::stod(fd.GetFilterParams()[0]);
  if (threshold > 1 || threshold < 0) {
    std::logic_error("incorrect value for edge filter");
  }
  EdgeDetection *new_filter = new EdgeDetection(threshold);
  return new_filter;
}

Filter *SharpeningFilterMaker(const FilterDescriptor &fd) {
  Sharpening *new_filter = new Sharpening();
  return new_filter;
}

// Filter *BlurFilterMaker(const FilterDescriptor &fd) {
//  double sigma = std::stod(fd.GetFilterParams()[0]);
//  Blur *new_filter = new Blur(sigma);
//  return new_filter;
// }

FiltersProducers::FiltersProducers() {
  filter_producers_["crop"] = CropFilterMaker;
  filter_producers_["neg"] = NegativefilterMaker;
  filter_producers_["gs"] = GrayscaleFilterMaker;
  filter_producers_["edge"] = EdgeDetectionFilterMaker;
  filter_producers_["sharp"] = SharpeningFilterMaker;
  // filter_producers_["blur"] = BlurFilterMaker;
}

FiltersProducers::PFilterProducer
FiltersProducers::Find(std::map<std::string, PFilterProducer> &filter_producers,
                       const std::string &filter_name) const {
  PFilterProducer producer = filter_producers[filter_name];
  if (!producer) {
    throw std::runtime_error("введено некорректное имя фильтра.");
  }
  return producer;
}
