
#ifndef IMG_PROC_BMP_H
#define IMG_PROC_BMP_H

#include "matrix.h"
#include <cstdint>

// В оперативной памяти большинства архитектур хранятся в формате little-endian
// (младшие байты по младшим адресам). Например, число 298 будет храниться в
// виде 4 байт в шестнадцатиричной нотации: 2A 01 00 00. В bmp файле числа
// хранятся тоже в little-endian, поэтому мы можем читать их и записывать
// непосредственно.

struct BmpHeader {
  int16_t BM;
  uint32_t bytes_size;
  int16_t reserved1;
  int16_t reserved2;
  uint32_t bitmap_offset;

} __attribute__((packed));

struct BitmapInfoHeader {
  uint32_t header_size;
  int32_t BMP_width;
  int32_t BMP_height;
  uint16_t color_planes;
  uint16_t bits_per_pixel;
  uint32_t compression;
  uint32_t raw_bitmap_data_size;
  int32_t horizontal_resolution;
  int32_t vertical_resolution;
  uint32_t palette_colors;
  uint32_t number_of_important_colors;
} __attribute__((packed));

struct Pixel {
  uint8_t b;
  uint8_t g;
  uint8_t r;
} __attribute__((packed));

struct BMP {
  BmpHeader bmp_header;
  BitmapInfoHeader bmp_info_header;
  Matrix<Pixel> data_matrix;

  explicit BMP(char *input_file_path);

  void LoadBmp(char *file_path);

  void SaveBmp(char *file_path);
};

#endif // IMG_PROC_BMP_H
