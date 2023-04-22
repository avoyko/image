#include "grayscale.h"

void Grayscale::Apply(const std::vector<std::string> &parameters, Image &image) {
    for (std::vector<Pixel> &pixel_array : image.data_) {
        for (Pixel &pixel : pixel_array) {

            double red = static_cast<double>(pixel.r) / max_size;
            double green = static_cast<double>(pixel.g) / max_size;
            double blue = static_cast<double>(pixel.b) / max_size;

            uint8_t new_value = static_cast<uint8_t>(
                std::round((red_const_ * red + green_const_ * green + blue_const_ * blue) * max_size));

            pixel = {new_value, new_value, new_value};
        }
    }
}