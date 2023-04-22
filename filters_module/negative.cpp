#include "negative.h"

void Negative::Apply(const std::vector<std::string> &parameters, Image &image) {
    for (std::vector<Pixel> &pixel_array : image.data_) {
        for (Pixel &pixel : pixel_array) {

            uint8_t new_red = ConvertToChar(1 - (ConvertToDouble(pixel.r)));

            uint8_t new_green = ConvertToChar(1 - (ConvertToDouble(pixel.g)));

            uint8_t new_blue = ConvertToChar(1 - (ConvertToDouble(pixel.b)));

            pixel = {new_blue, new_green, new_red};
        }
    }
}
