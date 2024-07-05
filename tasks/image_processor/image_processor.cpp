
#include "exception"
#include "pipeline_factory.h"
#include "producer.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  try {
    CmdLineParser cmdlinearguments(argc, argv);
    char *inp = cmdlinearguments.GetInputFile();
    char *out = cmdlinearguments.GetOutputFile();
    BMP bmp = BMP(inp);
    FiltersFactory factory = FiltersFactory(cmdlinearguments);
    Pipeline pipeline = Pipeline(factory);
    for (Filter *filter : pipeline.GetOperations()) {
      filter->Apply(bmp);
    }
    bmp.SaveBmp(out);
  } catch (const std::exception &error) {
    std::cerr << error.what() << std::endl;
    return -1;
  } catch (...) {
    std::cout << "rare mistake" << std::endl;
    return -2;
  }
}
