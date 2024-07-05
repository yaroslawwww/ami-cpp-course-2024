#include "cmdlineparser.h"
#include <iostream>
#include <stdexcept>

namespace leap_c {
const int FILTERS_BEGINNING_NUMBER = 3;
}

bool NotIsFilterName(char first_character) { return first_character != '-'; }

void CmdLineParser::ExtractFilters(int argc, char *argv[]) {
  int i = leap_c::FILTERS_BEGINNING_NUMBER;
  while (i < argc) {
    std::string filter_name = ++argv[i];
    FilterDescriptor new_filter(filter_name);
    ++i;
    while (i < argc && NotIsFilterName(*argv[i])) {
      new_filter.AddParam(std::string(argv[i]));
      ++i;
    }
    filters_.push_back(new_filter);
  }
}

CmdLineParser::CmdLineParser(int argc, char *argv[]) {
  if (argc < leap_c::FILTERS_BEGINNING_NUMBER) {
    throw std::logic_error(
        "к сожалению вы ввели недостаточное количество параметров.");
  }

  input_file_ = argv[1];
  output_file_ = argv[2];
  ExtractFilters(argc, argv);
  std::cout << "input_file: " << input_file_ << std::endl;
  std::cout << "output_file: " << output_file_ << std::endl;
}

void CmdLineParser::RevealFiltersList() {
  // функция для визуальной проверки полученных значений
  for (const FilterDescriptor &filter : filters_) {
    std::cout << filter.GetFilterName() << std::endl;
    for (const std::string &param : filter.GetFilterParams()) {
      std::cout << param << " ";
    }
    std::cout << std::endl;
  }
}
