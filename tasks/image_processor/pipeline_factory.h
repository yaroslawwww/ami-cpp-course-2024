//
// Created by yarik on 27.03.24.
//

#ifndef GRAPHICSSNIPPETS_FACTORY_H
#define GRAPHICSSNIPPETS_FACTORY_H

#include "cmdlineparser.h"
#include "producer.h"
#include <map>
#include <stdexcept>
#include <vector>

class FiltersFactory {
  FiltersProducers producers_;

  Filter *MakeFilter(const FilterDescriptor &fd);

  std::vector<Filter *> operations_;

public:
  std::vector<Filter *> &GetCmdOperations() { return operations_; }

  explicit FiltersFactory(CmdLineParser &cmdlineparser);
};

class Pipeline {
private:
  std::vector<Filter *> operations_;

public:
  std::vector<Filter *> GetOperations() { return operations_; }

  explicit Pipeline(FiltersFactory &ff);

  ~Pipeline();
};

#endif // GRAPHICSSNIPPETS_FACTORY_H
