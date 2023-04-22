#include "sharp.h"

void Sharpening::Apply(const std::vector<std::string>& parameters, Image& image) {

    const size_t height = image.GetHeight();
    const size_t width = image.GetWidth();
    Vector new_pixel_data;

    for (size_t i = 0; i < height; ++i) {

        new_pixel_data.push_back({});

        for (size_t j = 0; j < width; ++j) {
            std::vector<Pixel> neighbours = image.GenerateNeighbours(static_cast<int>(i), static_cast<int>(j));

            Pixel pixel;
            pixel.r = ConvertToChar(this->ApplyMatrixMain(neighbours, sharp_matrix_, "red"));
            pixel.g = ConvertToChar(this->ApplyMatrixMain(neighbours, sharp_matrix_, "green"));
            pixel.b = ConvertToChar(this->ApplyMatrixMain(neighbours, sharp_matrix_, "blue"));

            new_pixel_data[i].push_back(pixel);
        }
    }
    image.data_ = new_pixel_data;
}
