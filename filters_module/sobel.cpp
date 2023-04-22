#include "sobel.h"

void Sobel::Apply(const std::vector<std::string>& parameters, Image& image) {

    const size_t height = image.GetHeight();
    const size_t width = image.GetWidth();
    Vector new_pixel_data;

    Grayscale::Apply(parameters, image);

    for (size_t i = 0; i < static_cast<size_t>(height); ++i) {

        new_pixel_data.push_back({});

        for (size_t j = 0; j < static_cast<size_t>(width); ++j) {
            std::vector<Pixel> neighbours = image.GenerateNeighbours(static_cast<int>(i), static_cast<int>(j));

            Pixel pixel;

            double x_red = this->ApplyMatrixMain(neighbours, horizontal_matrix_, "red");
            double x_green = this->ApplyMatrixMain(neighbours, horizontal_matrix_, "green");
            double x_blue = this->ApplyMatrixMain(neighbours, horizontal_matrix_, "blue");

            double y_red = this->ApplyMatrixMain(neighbours, vertical_matrix_, "red");
            double y_green = this->ApplyMatrixMain(neighbours, vertical_matrix_, "green");
            double y_blue = this->ApplyMatrixMain(neighbours, vertical_matrix_, "blue");

            uint8_t red = ConvertToChar(std::min(1.0, std::sqrt(x_red * x_red + y_red * y_red)));
            uint8_t green = ConvertToChar(std::min(1.0, std::sqrt(x_green * x_green + y_green * y_green)));
            uint8_t blue = ConvertToChar(std::min(1.0, std::sqrt(x_blue * x_blue + y_blue * y_blue)));

            pixel = {blue, green, red};

            new_pixel_data[i].push_back(pixel);
        }
    }
    image.data_ = new_pixel_data;
}
