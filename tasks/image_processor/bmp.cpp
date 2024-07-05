#include "bmp.h"
#include <fstream>
#include <iostream>

namespace leap_c {
const size_t PIXEL_SIZE = 3;
}

void BMP::LoadBmp(char *file_path) {
  std::ifstream file(file_path, std::ios_base::binary);
  if (!file.is_open()) {
    throw std::runtime_error(std::string("Could not open file ") +
                             std::string(file_path));
  }
  file.read(reinterpret_cast<char *>(&bmp_header), sizeof(bmp_header));
  file.read(reinterpret_cast<char *>(&bmp_info_header),
            sizeof(bmp_info_header));
  data_matrix =
      Matrix<Pixel>(bmp_info_header.BMP_height, bmp_info_header.BMP_width);
  int padding = (4 - (bmp_info_header.BMP_width * 3) % 4) % 4;
  for (int32_t i = 0; i < bmp_info_header.BMP_height; ++i) {
    for (int32_t j = 0; j < bmp_info_header.BMP_width; ++j) {
      Pixel pixel{};
      file.read(reinterpret_cast<char *>(&pixel),
                sizeof(uint8_t) * leap_c::PIXEL_SIZE);
      data_matrix[bmp_info_header.BMP_height - i - 1][j] = pixel;
    }
    file.ignore(padding);
  }
  std::cout << "succesful download" << std::endl;

  file.close();
}

void BMP::SaveBmp(char *file_path) {
  std::ofstream file(file_path, std::ios_base::binary);
  if (!file.is_open()) {
    throw std::runtime_error(std::string("Could not open file") +
                             std::string(file_path));
  }
  file.write(reinterpret_cast<char *>(&bmp_header), sizeof(bmp_header));
  file.write(reinterpret_cast<char *>(&bmp_info_header),
             sizeof(bmp_info_header));
  int padding = (4 - (bmp_info_header.BMP_width * 3) % 4) % 4;
  char nullchar = 0;
  for (int32_t i = 0; i < bmp_info_header.BMP_height; ++i) {
    for (int32_t j = 0; j < bmp_info_header.BMP_width; ++j) {
      Pixel pixel = data_matrix[bmp_info_header.BMP_height - i - 1][j];
      file.write(reinterpret_cast<char *>(&pixel), sizeof(uint8_t) * 3);
    }
    for (int k = 0; k < padding; ++k) {
      file.write(&nullchar, 1);
    }
  }
  std::cout << "succesful save" << std::endl;
  file.close();
}

BMP::BMP(char *input_file_path) { LoadBmp(input_file_path); }
