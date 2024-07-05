
#include "pipeline_factory.h"

FiltersFactory::FiltersFactory(CmdLineParser &cmdlineparser) {
  for (const FilterDescriptor &filter_descriptor : cmdlineparser.GetFilters()) {
    operations_.push_back(MakeFilter(filter_descriptor));
  }
}

Filter *FiltersFactory::MakeFilter(const FilterDescriptor &fd) {
  FiltersProducers::PFilterProducer fp =
      producers_.Find(producers_.filter_producers_, fd.GetFilterName());
  Filter *new_filter = fp(fd);
  if (!new_filter) {
    throw std::logic_error("Продьюсер не сумер создать фильтр по fd, т.к. либо "
                           "параметры не ок, либо что-то другое");
  }
  return new_filter;
}

Pipeline::Pipeline(FiltersFactory &ff) { operations_ = ff.GetCmdOperations(); }

Pipeline::~Pipeline() {
  for (auto filter : operations_) {
    delete filter;
  }
}