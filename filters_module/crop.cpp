#include "crop.h"
#include "stdexcept"

void Crop::Apply(const std::vector<std::string>& parameters, Image& image) {
    if (parameters.size() == default_parameters_size) {
        size_t width = std::stoi(parameters[0]);
        size_t height = std::stoi(parameters[1]);

        if (width >= image.GetWidth() || height >= image.GetHeight()) {
            return;
        }

        image.Resize(height, width);

        size_t new_height = image.data_.size();
        size_t new_width = image.data_[0].size();

        image.SetHeight(new_height);
        image.SetWidth(new_width);
    } else {
        throw Exception("Incorrect parameters for crop filter");
    }
}
