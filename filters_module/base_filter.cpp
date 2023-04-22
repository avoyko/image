
#include "base_filter.h"

double Filters::ApplyMatrixMain(const std::vector<Pixel>& pixel_matrix, const std::vector<int>& filter_matrix,
                                std::string base_color) const {
    double weighted_sum = 0;
    for (size_t i = 0; i < pixel_matrix.size(); ++i) {

        weighted_sum += ConvertToDouble(pixel_matrix[i][base_color]) * (filter_matrix[i]);
    }
    return (std::min(1.0, std::max(0.0, weighted_sum)));
}

double Filters::ConvertToDouble(uint8_t color) const {
    return static_cast<double>(color) / max_size;
}

uint8_t Filters::ConvertToChar(double color) const {
    return static_cast<uint8_t>(std::min(max_size, std::round(color * max_size)));
}
