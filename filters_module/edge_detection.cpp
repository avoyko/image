#include "edge_detection.h"

void EdgeDetection::Apply(const std::vector<std::string> &parameters, Image &image) {

    if (parameters.size() == default_parameters_size) {
        const double threshold = (std::stod(parameters[0]));
        const size_t height = image.GetHeight();
        const size_t width = image.GetWidth();
        Vector new_pixel_data;

        Grayscale::Apply(parameters, image);

        for (size_t i = 0; i < static_cast<size_t>(height); ++i) {

            new_pixel_data.push_back({});

            for (size_t j = 0; j < static_cast<size_t>(width); ++j) {
                std::vector<Pixel> neighbours = image.GenerateNeighbours(static_cast<int>(i), static_cast<int>(j));

                Pixel pixel;
                pixel.r = ConvertToChar(this->ApplyMatrixMain(neighbours, edge_matrix_, "red"));
                pixel = {pixel.r, pixel.r, pixel.r};
                ThresholdControl(threshold, pixel);
                new_pixel_data[i].push_back(pixel);
            }
        }
        image.data_ = new_pixel_data;
    } else {
        throw Exception("Incorrect parameters for edge_detection filter");
    }
}

void EdgeDetection::ThresholdControl(double threshold, Pixel &pixel) {

    const Pixel white = {255, 255, 255};
    const Pixel black = {0, 0, 0};
    pixel = ConvertToDouble(pixel.r) > threshold ? white : black;
}
