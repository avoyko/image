#include "gauss_blur.h"

void GaussianBlur::Apply(const std::vector<std::string> &parameters, Image &image) {
    if (parameters.size() == default_parameters_size) {
        const double sigma = std::stod(parameters[0]);
        const size_t height = image.GetHeight();
        const size_t width = image.GetWidth();
        const int ratio = std::ceil(3 * sigma / regulator);
        HorizontalBlur(image.data_, width, height, ratio, sigma);
        VerticalBlur(image.data_, width, height, ratio, sigma);
    } else {
        throw Exception("Incorrect parameters for gaussian_blur filter");
    }
}

void GaussianBlur::HorizontalBlur(Vector &pixel_data, const size_t width, const size_t height, const int ratio,
                                  const double sigma) {

    std::vector<double> window(2 * ratio + 1, 0);
    Vector new_pixel_data;

    for (int i = ratio - 1; i >= 0; --i) {
        double power = static_cast<double>(-(i + 1) * (i + 1)) / (2 * sigma * sigma * pi);
        window[i] = std::pow(euler, power);
        window[window.size() - 1 - i] = window[i];
    }

    window[window.size() / 2] = 1;

    for (size_t i = 0; i < height; ++i) {

        new_pixel_data.push_back({});

        for (size_t j = 0; j < width; ++j) {

            double weighted_sum = 0;
            Pixel pixel_to_add;

            double new_red = 0;
            double new_green = 0;
            double new_blue = 0;

            for (size_t k = 0; k < window.size(); ++k) {

                int index = static_cast<int>(j + k) - ratio;

                if (index >= 0 && index < static_cast<int>(width)) {
                    Pixel pixel_to_change = pixel_data[i][index];

                    new_red += ConvertToDouble(pixel_to_change.r) * window[k];
                    new_green += ConvertToDouble(pixel_to_change.g) * window[k];
                    new_blue += ConvertToDouble(pixel_to_change.b) * window[k];
                    weighted_sum += window[k];
                }

                pixel_to_add.r = ConvertToChar((new_red) / weighted_sum);
                pixel_to_add.g = ConvertToChar((new_green) / weighted_sum);
                pixel_to_add.b = ConvertToChar((new_blue) / weighted_sum);
            }

            new_pixel_data[i].push_back(pixel_to_add);
        }
    }
    pixel_data = new_pixel_data;
}

void GaussianBlur::VerticalBlur(Vector &pixel_data, const size_t width, const size_t height, const int ratio,
                                const double sigma) {

    std::vector<double> window(2 * ratio + 1, 0);
    Vector new_pixel_data = {height, {width, {0, 0, 0}}};

    for (int i = ratio - 1; i >= 0; --i) {
        double power = (static_cast<double>(-(i + 1) * (i + 1))) / (2 * sigma * sigma * pi);
        window[i] = std::pow(euler, power);
        window[window.size() - 1 - i] = window[i];
    }

    window[window.size() / 2] = 1;

    for (size_t i = 0; i < width; ++i) {

        for (size_t j = 0; j < height; ++j) {

            double weighted_sum = 0;
            Pixel pixel_to_add;

            double new_red = 0;
            double new_green = 0;
            double new_blue = 0;

            for (size_t k = 0; k < window.size(); ++k) {

                int index = static_cast<int>(j + k) - ratio;

                if (index >= 0 && index < static_cast<int>(height)) {
                    Pixel pixel_to_change = pixel_data[index][i];

                    new_red += ConvertToDouble(pixel_to_change.r) * window[k];
                    new_green += ConvertToDouble(pixel_to_change.g) * window[k];
                    new_blue += ConvertToDouble(pixel_to_change.b) * window[k];
                    weighted_sum += window[k];
                }

                pixel_to_add.r = ConvertToChar((new_red) / weighted_sum);
                pixel_to_add.g = ConvertToChar((new_green) / weighted_sum);
                pixel_to_add.b = ConvertToChar((new_blue) / weighted_sum);
            }

            new_pixel_data[j][i] = pixel_to_add;
        }
    }

    pixel_data = new_pixel_data;
}
