#include <cstddef>
#include <vector>
#include <string>
#include <fstream>
#include "stdint.h"
#include <iostream>
#include <sstream>
#include <cstdint>
#include "../cmd/exceptions.h"

#ifndef CPP_HSE_BMP_H
#define CPP_HSE_BMP_H

// CPP_HSE_BMP_H

struct BmpHeader {
    uint16_t file_type;
    uint32_t file_size;
    uint16_t reserved_space1;
    uint16_t reserved_space2;
    uint32_t offset_info;

} __attribute__((__packed__));

struct BitmapInfoHeader {
    uint32_t bitmap_header_size;
    uint32_t pixel_width;
    uint32_t pixel_height;
    uint16_t color_planes;
    uint16_t bits_per_pixel;
    uint32_t compression_method;
    uint32_t raw_bitmap_data_size;
    uint32_t horizontal_resolution;
    uint32_t vertical_resolution;
    uint32_t palette_colors;
    uint32_t important_colors;
} __attribute__((__packed__));

struct Pixel {
    uint8_t b = 0;
    uint8_t g = 0;
    uint8_t r = 0;

    /// Sometimes i want to get color with index just for convenience
    auto operator[](std::string color) const {

        if (color == "blue") {
            return this->b;

        } else if (color == "green") {
            return this->g;

        } else {
            return this->r;
        }
    }

} __attribute__((__packed__));

using Vector = std::vector<std::vector<Pixel>>;

class Image;

class BMP {
public:
    /// Constructor
    explicit BMP(std::string input_file, std::string output_file) {
        bmp_file_input_name_ = input_file;
        bmp_file_output_name_ = output_file;
        LoadBMP();
    }

    /// Class functions
    void Exit(std::string exit_output);

    void LoadBMP();

    void StreamLoadBMP(std::istream& stream);

    void SaveBMP(Image& image);

    void StreamSaveBMP(std::ostream& stream);

    void CreatePixelData(const size_t height, const size_t width);

    /// Class fields
    std::string bmp_file_input_name_;
    std::string bmp_file_output_name_;
    BmpHeader bmp_file_header_;
    BitmapInfoHeader bmp_info_header_;
    std::vector<std::vector<Pixel>> pixel_data_;

    /// Important constants
    const uint16_t default_file_type = 0x4D42;
    const int default_header_size = 54;
    const int max_size = 255;
    const uint16_t default_bits_per_pixel_ = 24;
};

class Image {
public:
    /// Class constructor
    explicit Image(std::vector<std::vector<Pixel>> pixel_data) {
        data_ = pixel_data;
        width_ = pixel_data[0].size();
        height_ = pixel_data.size();
    }

    /// Class functions
    void Resize(size_t new_height, size_t new_width);

    void SetHeight(size_t height);

    void SetWidth(size_t width);

    size_t GetHeight() const;

    size_t GetWidth() const;

    std::vector<Pixel> GenerateNeighbours(int x, int y);

    /// Class fields
    std::vector<std::vector<Pixel>> data_;
    size_t width_ = 0;
    size_t height_ = 0;
};

#endif