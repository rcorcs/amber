
#pragma once

#include "Pixel.h"

#include <cstdio>
#include <cstddef>

class Image : public NArray<PixelRef::value_type, 3> {
using Base = NArray<PixelRef::value_type, 3>;
public:
  enum FileFormat { JPEG, PNG };

  PixelRef get(size_t row, size_t col) {
    return PixelRef(&at(row, col, 0), Base::depth());
  }
};

class ImageIO {
private:
  static bool isPNG(FILE *file);
  static bool isJPEG(FILE *file);
  static bool readPNG(FILE *file, Image &img);
  static bool readJPEG(FILE *file, Image &img);

public:
  static Image loadFromFile(const char *filepath);
  static Image loadFromFile(const char *filepath, Image::FileFormat fmt);

  static void writeJPEG(Image &img, const char *filepath, int quality);
};
